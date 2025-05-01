/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:20:26 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/01 17:45:59 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(char *cmd, char **args)
{
    if (strcmp(cmd, "env") == 0)
    {
        cmd_env();
        return (0);
    }
    else if (strcmp(cmd, "export") == 0)
    {
        if (!args[1])
            fprintf(stderr, "export: usage: export VAR=value\n");
        else
            cmd_export(args);
        return (0);
    }
    else if (strcmp(cmd, "unset") == 0)
    {
        if (!args[1])
            fprintf(stderr, "unset: usage: unset VAR\n");
        else
            cmd_unset(args);
        return (0);
    }
    return (-1);
}

void cmd_echo(char **argv)
{
    int i;
    int newline;
    
    i = 1;
    newline = 1;

    if (argv[i] && strcmp(argv[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}
void cmd_cd(char **argv)
{
    if (!argv[1])
    {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }
    if (chdir(argv[1]) != 0)
        perror("cd");
}

void cmd_pwd(void)
{
    char cwd[4096];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}
void cmd_exit(char **argv)
{
    int exit_status;
    
    exit_status = 0;
    if (argv[1])
        exit_status = atoi(argv[1]);
    exit(exit_status);
}

