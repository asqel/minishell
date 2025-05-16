/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:49:58 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/16 18:20:01 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_env(t_msh_ctx *ctx)
{
    int i;

    i = 0;
    while (i < ctx->env_len)
    {
        if (ctx->env[i].value)
            printf("%s=%s\n", ctx->env[i].name, ctx->env[i].value);
        else
            printf("%s\n", ctx->env[i].name);
        i++;
    }
    return (0);
}

void builtin_export(t_env **env, char **args)
{
    (void)env;
    (void)args;
    // int i = 1;
    // if (!args[1])
    // {
    //     t_env *tmp = *env;
    //     while (tmp)
    //     {
    //         printf("declare -x %s", tmp->key);
    //         if (tmp->value)
    //             printf("=\"%s\"", tmp->value);
    //         printf("\n");
    //         tmp = tmp->next;
    //     }
    //     return;
    // }

    // while (args[i])
    // {
    //     char *equal = ft_strchr(args[i], '=');
    //     if (equal)
    //     {
    //         size_t len = equal - args[i];
    //         char *key = strndup(args[i], len);
    //         char *val = strdup(equal + 1);
    //         if (!is_valid_key(key))
    //             printf("export: `%s`: not a valid identifier\n", args[i]);
    //         else
    //             env_set(env, key, val);
    //         free(key);
    //         free(val);
    //     }
    //     else
    //     {
    //         if (!is_valid_key(args[i]))
    //             printf("export: `%s`: not a valid identifier\n", args[i]);
    //         else
    //             env_set(env, args[i], "");
    //     }
    //     i++;
    // }
}

int builtin_unset(int argc, char **argv, t_msh_ctx *ctx)
{
    int i;

    i = 1;
    while (i < argc)
    {
        msh_unset_env(ctx, argv[i]);
        i++;
    }
    return (0);
}
