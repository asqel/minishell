/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:38:30 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/15 16:07:16 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

char	*shell_read_line(void)
{
	char	*buf;
	size_t	bufsize;
	char	cwd[BUFSIZ];
	char	*line;

	line = readline(G "minishell$ " RST);
	if (line && *line)
		add_history(line);
	return (line);
	ft_getcwd(cwd, sizeof(cwd));
	printf(C " %s" RST "$>", cwd);
	buf = NULL;
	if (getline(&buf, &bufsize, stdin) == -1)
	{
		free(buf);
		buf = NULL;
		if (feof(stdin))
			printf(RED "[EOF]" RST);
		else
			printf(RED "Getline failed" RST);
	}
	return (buf);
}

static void	fork_and_exec(t_msh_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit_with_error("fork");
	if (pid == 0)
	{
		handle_redirs(*cmd);
		if (strchr(cmd->name, '/'))
			execve(cmd->name, cmd->argv, environ);
		else
			try_exec_in_path(cmd);
		perror("command not found");
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
}

void	try_exec_in_path(t_msh_cmd *cmd)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	full_path = NULL;
	i = 0;
	while (paths && paths[i])
	{
		full_path = join_path(paths[i], cmd->name);
		if (access(full_path, X_OK) == 0)
			execve(full_path, cmd->argv, environ);
		free(full_path);
		i++;
	}
	free_split(paths);
}

static void	run_command(t_msh_cmd *cmd)
{
	if (!cmd || !cmd->name)
		return ;
	if (cmd->is_builtin)
	{
		return ;
	}
	fork_and_exec(cmd);
}
