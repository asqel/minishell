/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:40:59 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/07 21:10:44 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exec(t_msh_cmd *cmds, int cmd_count)
{
	int		i;
	int		in_fd;
	int		pipefds[2];
	pid_t	pid;

	i = 0;
	in_fd = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if ((i < cmd_count - 1 && pipe(pipefds) == -1) || pid < 0)
			exit_with_error("pipe or fork");
		if (pid == 0)
			execute_child(cmds, i, in_fd, pipefds);
		if (in_fd != 0)
			close(in_fd);
		if (i < cmd_count - 1)
		{
			close(pipefds[1]);
			in_fd = pipefds[0];
		}
		waitpid(pid, NULL, 0);
		i++;
	}
}

void	execute_child(t_msh_cmd *cmds, int i, int in_fd, int pipefds[2])
{
	handle_redirs(cmds[i]);
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (pipefds && i < 256)
	{
		close(pipefds[0]);
		dup2(pipefds[1], STDOUT_FILENO);
		close(pipefds[1]);
	}
	execvp(cmds[i].name, cmds[i].argv);
	exit(EXIT_FAILURE);
}

void	handle_redirs(t_msh_cmd cmd)
{
	int	fd;

	if (cmd.redir_in)
		handle_redir_in(cmd);
	if (cmd.redir_out)
	{
		fd = open(cmd.redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit_with_error("open out");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (cmd.append_out)
	{
		fd = open(cmd.append_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit_with_error("open append");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_redir_in(t_msh_cmd cmd)
{
	int	fd;

	if (cmd.redir_in)
	{
		fd = open(cmd.redir_in, O_RDONLY);
		if (fd == -1)
			exit_with_error("open in");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	exit_with_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
