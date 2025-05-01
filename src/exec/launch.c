/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:23:21 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/01 19:17:33 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

int is_executing(int set_val, int val)
{
	static int executing = 0;
	if (set_val)
		executing = val;
	return executing;
}

void	msh_launch_file(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	if (0 == access(cmd->path, F_OK) && 0 == access(cmd->path, X_OK))
	{
		execve(cmd->path, cmd->argv, msh_build_env(ctx));
		exit(127); // !TODO: free
	}
	else
	{
		//msh_free_cmd(cmd); TODO
		//msh_free_ctx(ctx); TODO
		printf("Command not found\n");
		exit(127);
	}
}

static void do_redir(t_msh_cmd *cmd)
{
	int tmp;

	if (cmd->redir_out != NULL)
	{
		tmp = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(tmp, STDOUT_FILENO);
		close(tmp);
	}
	if (cmd->redir_in != NULL)
	{
		tmp = open(cmd->redir_in, O_RDONLY);
		dup2(tmp, STDIN_FILENO);
		close(tmp);
	}
	if (cmd->append_out != NULL)
	{
		tmp = open(cmd->append_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(tmp, STDOUT_FILENO);
		close(tmp);
	}
}

void	msh_exec_cmd_single(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	// do things with pipe
	int pid = fork();
	is_executing(1, 1);
	if (pid == 0)
	{
		do_redir(cmd);
		msh_launch_file(ctx, cmd);
	}
	waitpid(pid, &ctx->last_status, 0);
	is_executing(0, 0);
}

static void close_pipes(t_msh_process *processes, int cmd_len)
{
	for (int i = 0; i < cmd_len - 1; i++)
	{
		close(processes[i].fds[0]);
		close(processes[i].fds[1]);
	}
}

static void init_processes(t_msh_process *processes, t_msh_cmd *cmd, int cmd_len)
{
	for (int i = 0; i < cmd_len; i++)
	{
		processes[i].cmd = &cmd[i];
		processes[i].pid = 0;
		processes[i].status = 0;
		if (i < cmd_len - 1)
			pipe(processes[i].fds);
	}
}

static void launch_forks(t_msh_process *processes, int cmd_len, t_msh_ctx *ctx)
{
	for (int i = 0; i < cmd_len; i++)
	{
		processes[i].pid = fork();
		if (processes[i].pid == 0)
		{
			if (i == 0)
			{
				dup2(processes[i].fds[1], STDOUT_FILENO);
			}
			else if (i == cmd_len - 1)
			{
				dup2(processes[i - 1].fds[0], STDIN_FILENO);
			}
			else
			{
				dup2(processes[i - 1].fds[0], STDIN_FILENO);
				dup2(processes[i].fds[1], STDOUT_FILENO);
			}
			close_pipes(processes, cmd_len);
			do_redir(processes[i].cmd);
			msh_launch_file(ctx, processes[i].cmd);
		}
	}
	close_pipes(processes, cmd_len);
	for (int i = 0; i < cmd_len - 1; i++)
		waitpid(processes[i].pid, &processes[i].status, 0);
}

void msh_exec_cmd_pipes(t_msh_ctx *ctx, t_msh_cmd *cmd, int cmd_len)
{
	t_msh_process *processes;

	processes = malloc(sizeof(t_msh_process) * cmd_len);
	if (!processes)
		return ;
	init_processes(processes, cmd, cmd_len);
	launch_forks(processes, cmd_len, ctx);
	waitpid(processes[cmd_len - 1].pid, &ctx->last_status, 0);
}