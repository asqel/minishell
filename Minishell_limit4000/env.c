/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:38:26 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/01 18:28:02 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void cmd_env(void)
{
    int i;

    i = 0;
    while (environ[i] != NULL) 
    {
        printf("%s\n", environ[i]);
        i++;
    }
}

char *get_env_variable(const char *name)
{
    return getenv(name);
}

int set_env_variable(const char *name, const char *value)
{
    return setenv(name, value, 1);
}

int unset_env_variable(const char *name)
{
    return unsetenv(name);
}
static void export_print_env(void)
{
    int i;
    
    i = 0;
    while (environ[i])
    {
        printf("declare -x %s\n", environ[i]);
        i++;
    }
}

void cmd_export(char **argv)
{
    int i;
    char *equal_sign;
    char *name;

    if (!argv[1])
    {
        export_print_env();
        return;
    }
    i = 1;
    while (argv[i])
    {
        equal_sign = strchr(argv[i], '=');
        if (equal_sign)
        {
            name = strndup(argv[i], equal_sign - argv[i]);
            if (!name)
            {
                perror("strndup");
                return;
            }
            unsetenv(name);
            free(name);
            putenv(argv[i]);
        }
        else
        {
            // si pas de '=', on peut soit ignorer, soit exporter une variable vide
            // comportement bash : exporter une variable sans valeur
            if (getenv(argv[i]) == NULL)
                putenv(argv[i]); // attention: ici, ça peut être une source de problème car putenv attend "VAR=VAL"
            // une vraie solution serait d'ajouter "VAR=" en concaténant
        }
        i++;
    }
}
void cmd_unset(char **argv)
{
    int i;
    
    i = 1;

    while (argv[i])
    {
        if (unsetenv(argv[i]) == -1)
            perror("unset");
        i++;
    }
}
