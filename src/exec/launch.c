/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:23:21 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/23 20:31:19 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

void	msh_launch_file(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	if (0 == access(cmd->path, F_OK) && 0 == access(cmd->path, X_OK))
	{
		int x = execve(cmd->path, cmd->argv, msh_build_env(ctx));
		printf("ici %d\n", x);
	}
	else
	{
		//msh_free_cmd(cmd); TODO
		//msh_free_ctx(ctx); TODO
		printf("Command not found\n");
		exit(127);
	}
}

int	msh_exec_cmd_single(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	int redir_fd[3]; // > >> <
	int tmp;

	redir_fd[0] = -2;
	redir_fd[1] = -2;
	redir_fd[2] = -2;
	tmp = -1;
	if (cmd->redir_out != NULL)
		tmp = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (tmp != -1)
		redir_fd[0] = tmp;
	tmp = -1;
	if (cmd->append_out != NULL)
		tmp = open(cmd->append_out, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (tmp != -1)
		redir_fd[1] = tmp;
	tmp = -1;
	if (cmd->redir_in != NULL)
		tmp = open(cmd->redir_in, O_RDONLY | O_CREAT, 0664);
	if (tmp != -1)
		redir_fd[2] = tmp;
	if (redir_fd[0] == -1 || redir_fd[1] == -1 || redir_fd[2] == -1)
	{
		printf("Error\n");
		exit(1);
	}
	// do things with pipe
	int pid = fork();
	if (pid == 0)
	{
		if (redir_fd[0] != -2)
        {
            dup2(redir_fd[0], STDOUT_FILENO);
            close(redir_fd[0]);
        }
        if (redir_fd[1] != -2)
        {
            dup2(redir_fd[1], STDOUT_FILENO);
            close(redir_fd[1]);
        }
        if (redir_fd[2] != -2)
        {
            dup2(redir_fd[2], STDIN_FILENO);
            close(redir_fd[2]);
        }
		msh_launch_file(ctx, cmd);
	}
	int i = -1;
	while (++i < 3)
		if (redir_fd[i] >= 0)
			close(redir_fd[i]);
	int res = 0;
	while (waitpid(pid, NULL, WNOHANG) <= 0)
	{
		if (g_last_signal == SIGINT) {
			kill(pid, SIGINT);
			g_last_signal = 0;
			res = 1;
		}
	}
	return res;
}
