/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:19:50 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/08 14:35:12 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	msh_ast_set_args(t_msh_cmd *cmd, char **argv, char *name)
{
	int	i;

	cmd->path = msh_find_cmd(name, &(cmd->is_builtin));
	cmd->argc = msh_array_len(argv) + 1;
	cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
	if (NULL == cmd->argv || NULL == cmd->path)
		return (msh_free(&cmd->argv), msh_free(&cmd->path));
	cmd->argv[cmd->argc] = NULL;
	cmd->argv[0] = ft_strdup(name);
	i = 0;
	while (++i < cmd->argc)
		cmd->argv[i] = ft_strdup(argv[i - 1]);
}

int msh_ast_new_command(char *name, int *err, t_msh_cmd *cmd)
{
	ft_memset(cmd, 0, sizeof())
}