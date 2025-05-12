/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:23:21 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/09 14:36:39 by axlleres         ###   ########.fr       */
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
		exit(127);
	}
	msh_free_ctx(ctx);
	print_error("Command not found\n");
	exit(127);
}

static void do_redir(t_msh_cmd *cmd)
{
	int tmp;

	if (cmd->redir_out != NULL && cmd->type_out == 1)
	{
		tmp = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(tmp, STDOUT_FILENO);
		close(tmp);
	}
	if (cmd->redir_in != NULL && cmd->type_in == 1)
	{
		tmp = open(cmd->redir_in, O_RDONLY);
		dup2(tmp, STDIN_FILENO);
		close(tmp);
	}
	if (cmd->append_out != NULL && cmd->type_out == 2)
	{
		tmp = open(cmd->append_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(tmp, STDOUT_FILENO);
		close(tmp);
	}
}

void exec_builtin(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "cd") == 0)
		ctx->last_status = msh_blt_cd(cmd->argc, cmd->argv);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		ctx->last_status = msh_blt_pwd(cmd->argc, cmd->argv);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		ctx->last_status = msh_blt_echo(cmd->argc, cmd->argv);
}

void	msh_exec_cmd_single(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	int pipes[2];

	if (cmd->is_builtin)
		return exec_builtin(ctx, cmd);
	// do things with pipe
	if (cmd->here_doc != NULL && cmd->type_in == 2)
	{
		pipe(pipes);
		write(pipes[1], cmd->here_doc, ft_strlen(cmd->here_doc));
		write(pipes[1], "\n", 1);
	}
	int pid = fork();
	is_executing(1, 1);
	if (pid == 0)
	{
		if (cmd->here_doc != NULL && cmd->type_in == 2)
		{
			dup2(pipes[0], STDIN_FILENO);
			close(pipes[0]);
			close(pipes[1]);
		}
		do_redir(cmd);
		msh_launch_file(ctx, cmd);
	}
	if (cmd->here_doc != NULL && cmd->type_in == 2)
		close(pipes[1]);
	if (cmd->here_doc != NULL && cmd->type_in == 2)
		close(pipes[0]);
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
	int heredoc_fd[2];

	if (processes[0].cmd->here_doc != NULL && processes[0].cmd->type_in == 2)
	{
		pipe(heredoc_fd);
		write(heredoc_fd[1], processes[0].cmd->here_doc, ft_strlen(processes[0].cmd->here_doc));
		write(heredoc_fd[1], "\n", 1);
	}
	for (int i = 0; i < cmd_len; i++)
	{
		processes[i].pid = fork();
		if (processes[i].pid == 0)
		{
			if (i == 0)
				dup2(processes[i].fds[1], STDOUT_FILENO);
			else if (i == cmd_len - 1)
				dup2(processes[i - 1].fds[0], STDIN_FILENO);
			else
			{
				dup2(processes[i - 1].fds[0], STDIN_FILENO);
				dup2(processes[i].fds[1], STDOUT_FILENO);
			}
			close_pipes(processes, cmd_len);
			do_redir(processes[i].cmd);
			if (processes[i].cmd->is_builtin)
				return exec_builtin(ctx, processes[i].cmd);
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