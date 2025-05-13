/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:23:21 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/12 18:26:18 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

int	msh_launch_file(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	char	**env;
	int		i;

	if (0 == access(cmd->path, F_OK) && 0 == access(cmd->path, X_OK))
	{
		env = msh_build_env(ctx);
		execve(cmd->path, cmd->argv, env);
		print_error("execve failed");
		if (env == NULL)
			return ;
		i = 0;
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
		return (0);
	}
	print_error("command not found");
	return (1);
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
			//do_redir(processes[i].cmd);
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