/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:48:26 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/05 17:01:17 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	const char	*builtins[7];
	int			i;

	builtins[0] = "cd";
	builtins[1] = "exit";
	builtins[2] = "env";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "echo";
	builtins[6] = NULL;

	i = 0;
	while (builtins[i])
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
void run_builtin(t_msh_cmd *cmd)
{
    if (strcmp(cmd->name, "echo") == 0)
        cmd_echo(cmd->argv);
    else if (strcmp(cmd->name, "cd") == 0)
        cmd_cd(cmd->argv);
    else if (strcmp(cmd->name, "pwd") == 0)
        cmd_pwd();
    else if (strcmp(cmd->name, "export") == 0)
        cmd_export(cmd->argv);
    else if (strcmp(cmd->name, "unset") == 0)
        cmd_unset(cmd->argv);
    else if (strcmp(cmd->name, "env") == 0)
        cmd_env();
    else if (strcmp(cmd->name, "exit") == 0)
        cmd_exit(cmd->argv);
    else
        fprintf(stderr, RED"Builtin non pris en charge : %s\n"RST, cmd->name);
}

