/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:38:30 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/12 18:23:42 by mgobert          ###   ########.fr       */
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
		run_builtin(cmd);
		return ;
	}
	fork_and_exec(cmd);
}

int	main(void)
{
	char		*line;
	t_msh_cmd	*cmds;
	int			cmd_count;
	int			i;

	i = 0;
	printbanner();
	while ((line = shell_read_line()))
	{
		if (!*line || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		cmd_count = parse_pipeline(line, &cmds);
		while (i < cmd_count)
		{
			run_command(&cmds[i]);
			free_command(&cmds[i]);
			i++;
		}
		printf("%d", cmds->type_in);
		free(cmds);
		free(line);
	}
	return (0);
}

/* int main(void)
{
	char		*line;
	t_msh_cmd	*cmds;
	int			cmd_count;

	printbanner();
	while ((line = shell_read_line()))
	{
		if (!*line)
		{
			free(line);
			continue ;
		}
		if (only_spaces(line))
{
	free(line);
	continue ;
}

		cmd_count = parse_pipeline(line, &cmds);
		printf(G"\nNombre de commandes détectées : %d\n"RST, cmd_count);

		for (int i = 0; i < cmd_count; i++)
		{
			t_msh_cmd cmd = cmds[i];
			printf(C"\n--- Commande #%d ---\n"RST, i + 1);
			printf("Nom       : %s\n", cmd.name ? cmd.name : "(null)");
			printf("Builtin   : %s\n", cmd.is_builtin ? "oui" : "non");
			printf("Arguments :\n");
			if (cmd.is_builtin)
			execute_builtin(cmd.name, cmd.argv);
			else
			shell_exec(&cmd, 1); // Exécute commande externe (même seule)
			for (int j = 0; j < cmd.argc; j++)
				printf("  argv[%d] = %s\n", j, cmd.argv[j]);

			if (cmd.redir_in)
				printf("Redir <   : %s\n", cmd.redir_in);
			if (cmd.redir_out)
				printf("Redir >   : %s\n", cmd.redir_out);
			if (cmd.append_out)
				printf("Redir >>  : %s\n", cmd.append_out);
			if (cmd.here_doc)
				printf("Redir <<  : %s\n", cmd.here_doc);
		}

		// Nettoyage
		for (int i = 0; i < cmd_count; i++)
		{
			free_command(&cmds[i]);
		}
		free(cmds);
	}
	return (0);
} */
