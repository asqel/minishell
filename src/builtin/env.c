/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:49:58 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/16 16:56:50 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *env_new(char *key, char *value)
{
    t_env *new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    return (new);
}

t_env *env_init(char **envp)
{
    t_env *head = NULL;
    t_env *current = NULL;
    for (int i = 0; envp[i]; i++)
    {
        char *equal = strchr(envp[i], '=');
        if (!equal)
            continue;
        char *key = ft_strndup(envp[i], equal - envp[i]);
        char *value = ft_strdup(equal + 1);
        t_env *new = env_new(key, value);
        free(key);
        free(value);
        if (!head)
            head = new;
        else
            current->next = new;
        current = new;
    }
    return (head);
}

void env_free(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

char *env_get(t_env *env, const char *key)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

void env_set(t_env **env, const char *key, const char *value)
{
    t_env *current = *env;
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    t_env *new = env_new((char *)key, (char *)value);
    new->next = *env;
    *env = new;
}

void env_unset(t_env **env, const char *key)
{
    t_env *current = *env;
    t_env *prev = NULL;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

char **env_to_tab(t_env *env)
{
    int count = 0;
    t_env *tmp = env;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    char **envp = malloc(sizeof(char *) * (count + 1));
    tmp = env;
    for (int i = 0; i < count; i++)
    {
        size_t len = ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2;
        envp[i] = malloc(len);
        snprintf(envp[i], len, "%s=%s", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    envp[count] = NULL;
    return envp;
}

int is_valid_key(const char *key)
{
    if (!key || !*key)
        return (0);
    if (!isalpha(*key) && *key != '_')
        return (0);
    while (*key)
    {
        if (!isalnum(*key) && *key != '_')
            return (0);
        key++;
    }
    return (1);
}

void builtin_env(t_env *env)
{
    while (env)
    {
        if (env->value && *(env->value))
            printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

void builtin_export(t_env **env, char **args)
{
    int i = 1;
    if (!args[1])
    {
        t_env *tmp = *env;
        while (tmp)
        {
            printf("declare -x %s", tmp->key);
            if (tmp->value)
                printf("=\"%s\"", tmp->value);
            printf("\n");
            tmp = tmp->next;
        }
        return;
    }
    while (args[i])
    {
        char *equal = strchr(args[i], '=');
        if (equal)
        {
            size_t len = equal - args[i];
            char *key = strndup(args[i], len);
            char *val = strdup(equal + 1);
            if (!is_valid_key(key))
                printf("export: `%s`: not a valid identifier\n", args[i]);
            else
                env_set(env, key, val);
            free(key);
            free(val);
        }
        else
        {
            if (!is_valid_key(args[i]))
                printf("export: `%s`: not a valid identifier\n", args[i]);
            else
                env_set(env, args[i], "");
        }
        i++;
    }
}

void builtin_unset(int argc, char **argv, t_msh_ctx *ctx)
{
    int i = 1;
    while (i < argc)
    {
        msh_unset_env(ctx, argv[i]);
        i++;
    }
} 