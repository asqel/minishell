/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:28:06 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/12 18:31:05 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void init_heredoc_pipe(int pipes[2], t_msh_cmd *cmd)
{
	if (cmd->here_doc != NULL && cmd->type_in == 2)
	{
		pipe(pipes);
		write(pipes[1], cmd->here_doc, ft_strlen(cmd->here_doc));
		write(pipes[1], "\n", 1);
	}
}

static void	read_heredoc(int pipes[2], t_msh_cmd *cmd)
{
	if (cmd->here_doc != NULL && cmd->type_in == 2)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		close(pipes[1]);
	}
}

static void close_heredoc(int pipes[2], t_msh_cmd *cmd)
{
	if (cmd->here_doc != NULL && cmd->type_in == 2)
	{
		close(pipes[0]);
		close(pipes[1]);
	}
}

static int do_redir(t_msh_cmd *cmd)
{
	if (cmd->redir_out != NULL && cmd->type_out == 1)
		if (msh_redir_out(cmd))
			return (1);
	if (cmd->redir_in != NULL && cmd->type_in == 1)
		if (msh_redir_in(cmd))
			return (1);
	if (cmd->append_out != NULL && cmd->type_out == 2)
		if (msh_redir_append(cmd))
			return (1);
	return (0);
}

void	msh_exec_cmd_single(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	int pipes[2];

	if (cmd->is_builtin)
		return exec_builtin(ctx, cmd);
	init_heredoc_pipe(pipes, cmd);
	int pid = fork();
	is_executing(1, 1);
	if (pid == 0)
	{
		read_heredoc(pipes, cmd);
		if (do_redir(cmd))
		{
			close_heredoc(pipes, cmd);
			msh_free_cmds(cmd, 1);
			msh_free_ctx(ctx);
			rl_clear_history();
			exit(1);
		}
		msh_launch_file(ctx, cmd);
	}
	close_heredoc(pipes, cmd);
	waitpid(pid, &ctx->last_status, 0);
	is_executing(0, 0);
}
