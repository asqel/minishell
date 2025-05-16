/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:23:21 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/16 20:10:41 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>

static void init_processes(t_msh_process *processes, t_msh_cmd *cmd, int cmd_len,t_msh_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < cmd_len)
	{
		processes[i].cmd = cmd;
		processes[i].ctx = ctx;
		pipe(processes[i].pipes);
		if (cmd[i].here_doc != NULL && cmd[i].type_in == 2)
		{
			pipe(processes[i].heredoc_pipes);
			write(processes[i].heredoc_pipes[1], cmd[i].here_doc,
				ft_strlen(cmd[i].here_doc));
			write(1, "\n", 1);
		}
	}
}

static void	msh_close_heredocs(t_msh_process *processes, int cmd_len)
{
	int	i;

	i = -1;
	while (++i < cmd_len)
	{
		if (processes[i].cmd[i].here_doc != NULL && processes[i].cmd[i].type_in == 2)
		{
			close(processes[i].heredoc_pipes[0]);
			close(processes[i].heredoc_pipes[1]);
		}
	}
}

static void close_pipes(t_msh_process *processes, int cmd_len)
{
	int	i;

	i = -1;
	while (++i < cmd_len)
	{
		close(processes[i].pipes[0]);
		close(processes[i].pipes[1]);
	}
	msh_close_heredocs(processes, cmd_len);
}

static int msh_redir_first(t_msh_process *processes, int cmd_len, int i)
{
	if (processes[i].cmd[i].redir_in != NULL && processes[i].cmd[i].type_in == 1)
		if (msh_redir_in(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].here_doc != NULL && processes[i].cmd[i].type_in == 2)
	{
		dup2(processes[i].heredoc_pipes[0], STDIN_FILENO);
		return (0);
	}
	if (processes[i].cmd[i].redir_out != NULL && processes[i].cmd[i].type_out == 1)
		if (msh_redir_out(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].append_out != NULL && processes[i].cmd[i].type_out == 2)
		if (msh_redir_append(processes[i].cmd + i))
			return (1);
	if (!processes[i].cmd[i].redir_out && !processes[i].cmd[i].append_out)
		dup2(processes[i].pipes[1], STDOUT_FILENO);
	close_pipes(processes, cmd_len);
	return (0);
}

static int msh_redir_last(t_msh_process *processes, int cmd_len, int i)
{
	if (processes[i].cmd[i].redir_in != NULL && processes[i].cmd[i].type_in == 1)
		if (msh_redir_in(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].here_doc != NULL && processes[i].cmd[i].type_in == 2)
	{
		dup2(processes[i].heredoc_pipes[0], STDIN_FILENO);
		return (0);
	}
	if (processes[i].cmd[i].redir_out != NULL && processes[i].cmd[i].type_out == 1)
		if (msh_redir_out(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].append_out != NULL && processes[i].cmd[i].type_out == 2)
		if (msh_redir_append(processes[i].cmd + i))
			return (1);
	if (!processes[i].cmd[i].redir_in && !processes[i].cmd[i].here_doc)
		dup2(processes[i - 1].pipes[0], STDIN_FILENO);
	close_pipes(processes, cmd_len);
	return (0);
}

static int msh_redir_middle(t_msh_process *processes, int cmd_len, int i)
{
	if (processes[i].cmd[i].redir_in != NULL && processes[i].cmd[i].type_in == 1)
		if (msh_redir_in(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].here_doc != NULL && processes[i].cmd[i].type_in == 2)
	{
		dup2(processes[i].heredoc_pipes[0], STDIN_FILENO);
		return (0);
	}
	if (processes[i].cmd[i].redir_out != NULL && processes[i].cmd[i].type_out == 1)
		if (msh_redir_out(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].append_out != NULL && processes[i].cmd[i].type_out == 2)
		if (msh_redir_append(processes[i].cmd + i))
			return (1);
	if (!processes[i].cmd[i].redir_in && !processes[i].cmd[i].here_doc)
		dup2(processes[i - 1].pipes[0], STDIN_FILENO);
	if (!processes[i].cmd[i].redir_out && !processes[i].cmd[i].append_out)
		dup2(processes[i].pipes[1], STDOUT_FILENO);
	close_pipes(processes, cmd_len);
	return (0);
}

// process[N] write to pipe[N]
// process[N] read to pipe[N - 1]
static int	msh_do_redir(t_msh_process *processes, int cmd_len, int i)
{
	if (i == 0)
		return (msh_redir_first(processes, cmd_len, i));
	if (i == cmd_len - 1)
		return (msh_redir_last(processes, cmd_len, i));
	return (msh_redir_middle(processes, cmd_len, i));
}

static void exec_file_piped(t_msh_process *processes, int cmd_len, t_msh_ctx *ctx, int i)
{
	char	**env;

	if (msh_is_executable(processes[i].cmd[i].path))
	{
		env = msh_build_env(ctx);
		execve(processes[i].cmd[i].path, processes[i].cmd[i].argv, env);
		free(env);
	}
	print_error_found(processes[i].cmd[i].name);
	msh_free_ctx(ctx);
	msh_free_cmds(processes[i].cmd, cmd_len);
	free(processes);
	rl_clear_history();
	exit(127);
}

static void exec_builtin_piped(t_msh_process *processes, int cmd_len, t_msh_ctx *ctx, int i)
{
	int status;

	if (ft_strcmp(processes[i].cmd[i].name, "exit") != 0)
	{
		exec_builtin(ctx, &processes[i].cmd[i]);
		status = ctx->last_status;
		msh_free_ctx(ctx);
		msh_free_cmds(processes[i].cmd, cmd_len);
		free(processes);
		rl_clear_history();
		exit(status);
	}
	msh_blt_exit2(processes, cmd_len, ctx, i);
}

static int *launch_forks(t_msh_process *processes, int cmd_len, t_msh_ctx *ctx)
{
	int	*pids;
	int	i;

	i = -1;
	pids = malloc(sizeof(int) * cmd_len);
	while (++i < cmd_len)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			free(pids);
			if (msh_do_redir(processes, cmd_len, i))
			{
				close_pipes(processes, cmd_len);
				msh_free_cmds(processes[i].cmd, cmd_len);
				msh_free_ctx(ctx);
				free(processes);
				rl_clear_history();
				exit(1);
			}
			processes[i].cmd[i].path = msh_find_cmd(processes[i].cmd[i].name,
					&processes[i].cmd[i].is_builtin, ctx);
			if (processes[i].cmd[i].is_builtin)
				exec_builtin_piped(processes, cmd_len, ctx, i);
			exec_file_piped(processes, cmd_len, ctx, i);
		}
	}
	return (pids);
}

void msh_exec_cmd_pipes(t_msh_ctx *ctx, t_msh_cmd *cmd, int cmd_len)
{
	t_msh_process	*processes;
	int				*pids;
	int				i;

	processes = malloc(sizeof(t_msh_process) * cmd_len);
	if (!processes)
		return ;
	init_processes(processes, cmd, cmd_len, ctx);
	is_executing(1, 1);
	pids = launch_forks(processes, cmd_len, ctx);
	is_executing(1, 0);
	close_pipes(processes, cmd_len);
	waitpid(pids[cmd_len - 1], &ctx->last_status, 0);
	i = -1;
	while(++i < cmd_len - 1)
		waitpid(pids[i], NULL, 0);
	free(pids);
	free(processes);
}
