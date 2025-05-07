/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:38:30 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/06 20:31:41 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

char *shell_read_line(void)
{
    char *buf;
    size_t bufsize;
    char cwd[BUFSIZ];
	char *line;
	line = readline(G "minishell$ " RST);
    if (line && *line)
        add_history(line);
    return line;
    Getcwd(cwd, sizeof(cwd));
    p(C" %s"RST"$>", cwd);
    buf = NULL; // pour getline on connait pas encore la taille du buffer
    if (getline(&buf, &bufsize, stdin) == -1)
    {
        free(buf);
        buf = NULL; // important de remettre le null parce qu'a l'echec ca change le buf
        if (feof(stdin))
            p(RED"[EOF]"RST);
        else
            p(RED"Getline failed"RST);
    }
    return (buf);
}

static void	fork_and_exec(t_msh_cmd *cmd)
{
	pid_t pid = fork();
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
	{
		int status;
		waitpid(pid, &status, 0);
	}
}
void	try_exec_in_path(t_msh_cmd *cmd)
{
	char *path;
	char **paths;
	char *full_path;
	int i;

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
	free_split(paths); // à toi d’implémenter
}
static void	run_command(t_msh_cmd *cmd)
{
	if (!cmd || !cmd->name)
		return;
	if (cmd->is_builtin)
	{
		run_builtin(cmd);
		return;
	}
	fork_and_exec(cmd);
}

// int main(void)
// {
//     char *line;
//     t_msh_cmd *cmds;
//     int cmd_count;

//     printbanner();
//     while ((line = shell_read_line()))
//     {
//         if (!*line || line[0] == '\n')
//         {
//             free(line);
//             continue;
//         }

//         cmd_count = parse_pipeline(line, &cmds);
//         for (int i = 0; i < cmd_count; i++)
//         {
//             run_command(&cmds[i]);
//             free_command(&cmds[i]);
//         }

//         free(cmds);
//         free(line);
//     }
//     return 0;
// }


/* int main(void)
{
    char *line;
    t_msh_cmd *cmds;
    int cmd_count;

    printbanner();

    while ((line = shell_read_line()))
	{
        if (!*line)
		{
            free(line);
            continue;
        }
		if (only_spaces(line))
{
    free(line);
    continue;
}

        cmd_count = parse_pipeline(line, &cmds);
        p(G"\nNombre de commandes détectées : %d\n"RST, cmd_count);

        for (int i = 0; i < cmd_count; i++)
		{
            t_msh_cmd cmd = cmds[i];
            p(C"\n--- Commande #%d ---\n"RST, i + 1);
            p("Nom       : %s\n", cmd.name ? cmd.name : "(null)");
            p("Builtin   : %s\n", cmd.is_builtin ? "oui" : "non");
            p("Arguments :\n");
			if (cmd.is_builtin)
        	execute_builtin(cmd.name, cmd.argv);
    		else
        	shell_exec(&cmd, 1); // Exécute commande externe (même seule)
            for (int j = 0; j < cmd.argc; j++)
                p("  argv[%d] = %s\n", j, cmd.argv[j]);

            if (cmd.redir_in)
                p("Redir <   : %s\n", cmd.redir_in);
            if (cmd.redir_out)
                p("Redir >   : %s\n", cmd.redir_out);
            if (cmd.append_out)
                p("Redir >>  : %s\n", cmd.append_out);
            if (cmd.here_doc)
                p("Redir <<  : %s\n", cmd.here_doc);
        }

        // Nettoyage
        for (int i = 0; i < cmd_count; i++)
		{
    		free_command(&cmds[i]);
		}
		free(cmds);
	}
	return 0;
} */

/* int main()
{
    printf("=== ENV ===\n");
    cmd_env();

    printf("\n=== SET VAR TEST ===\n");
    set_env_variable("MY_VAR", "hello");
    printf("MY_VAR = %s\n", get_env_variable("MY_VAR"));

    printf("\n=== EXPORT VAR2=test123 ===\n");
    cmd_export("VAR2=test123");
    printf("VAR2int main(void)
{
    char *line;
    t_msh_cmd *cmds;
    int cmd_count;
	int i;
	int y;

	i = 0;
	y = 0;
    printbanner();
    while ((line = shell_read_line()))
    {
        if (!*line || line[0] == '\n')
        {
            free(line);
            continue;
        }
        cmd_count = parse_pipeline(line, &cmds);
        while (i < cmd_count)
		{
            run_command(&cmds[i]);
			i++;
		}
        while (y < cmd_count)
		{
            free_command(&cmds[i]);
			y++;
		}
        free(cmds);
        free(line);
    }
    return (0);
}  = %s\n", get_env_variable("VAR2"));

    printf("\n=== UNSET VAR2 ===\n");
    cmd_unset("VAR2");
    printf("VAR2 = %s\n", get_env_variable("VAR2")); // devrait être NULL

    return 0;
} */