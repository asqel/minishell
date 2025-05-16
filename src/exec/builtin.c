/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:12:41 by axlleres          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/15 20:27:02 by axlleres         ###   ########.fr       */
=======
/*   Updated: 2025/05/16 15:13:21 by mgobert          ###   ########.fr       */
>>>>>>> a776b12 (env)
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

/* void exec_builtin(t_msh_ctx *ctx, t_msh_cmd *cmd)
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
<<<<<<< HEAD
		ctx->last_status = msh_blt_echo(cmd->argc, cmd->argv);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		ctx->last_status = msh_blt_exit(cmd, ctx, old_fd);
	dup2(old_fd, STDOUT_FILENO);
	close(old_fd);
=======
		ctx->last_status = msh_blt_echo(cmd->argc, cmd->argv, ctx);
	else if (ft_strcmp(cmd->name, "export") == 0)
		ctx->last_status = builtin_export()
	dup2(old_fd, STDOUT_FILENO);
	close(old_fd);
} */

void exec_builtin(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	int	old_fd;

	if (!msh_is_openable(cmd, cmd->redir_in))
	{
		ctx->last_status = 1;
		return ;
	}

	old_fd = dup(STDOUT_FILENO);
	if (msh_redir_blt(cmd)) // gère les redirections
		return ;

	if (ft_strcmp(cmd->name, "cd") == 0)
		ctx->last_status = msh_blt_cd(cmd->argc, cmd->argv, ctx);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		ctx->last_status = msh_blt_pwd(cmd->argc, cmd->argv, ctx);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		ctx->last_status = msh_blt_echo(cmd->argc, cmd->argv, ctx);
	else if (ft_strcmp(cmd->name, "export") == 0)
	{
		builtin_export(&ctx->env, cmd->argv);
		ctx->last_status = 0;
	}
	else if (ft_strcmp(cmd->name, "unset") == 0)
	{
		builtin_unset(&ctx->env, cmd->argv);
		ctx->last_status = 0;
	}
	else if (ft_strcmp(cmd->name, "env") == 0)
	{
		builtin_env(ctx->env);
		ctx->last_status = 0;
	}
	/* else if (ft_strcmp(cmd->name, "exit") == 0)
		ctx->last_status = msh_blt_exit(cmd->argc, cmd->argv, ctx); */ // à implémenter

	dup2(old_fd, STDOUT_FILENO);
	close(old_fd);
>>>>>>> a776b12 (env)
}
