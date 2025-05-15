/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:12:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/14 16:22:05 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

static int	msh_is_openable(t_msh_cmd *cmd, char *path)
{
	int	tmp;

	if (cmd->type_in == 2)
		return (1);
	if (cmd->redir_in == NULL)
		return (1);
	tmp = open(path, O_RDONLY);
	if (tmp == -1)
	{
		print_error_acces(path);
		return (0);
	}
	close(tmp);
	return (0);
}

int	msh_redir_blt(t_msh_cmd *cmd)
{
	if (msh_redir_out(cmd))
		return (1);
	if (msh_redir_append(cmd))
		return (1);
	return (0);
}

void exec_builtin(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	int	old_fd;

	if (!msh_is_openable(cmd, cmd->redir_in))
	{
		ctx->last_status = 1;
		return ;
	}
	old_fd = dup(STDOUT_FILENO);
	if (msh_redir_blt(cmd))
		return ;
	if (ft_strcmp(cmd->name, "cd") == 0)
		ctx->last_status = msh_blt_cd(cmd->argc, cmd->argv, ctx);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		ctx->last_status = msh_blt_pwd(cmd->argc, cmd->argv, ctx);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		ctx->last_status = msh_blt_echo(cmd->argc, cmd->argv, ctx);
	dup2(old_fd, STDOUT_FILENO);
	close(old_fd);
}