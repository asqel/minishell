/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:38:30 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/21 17:54:33 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_TOKENS 256

int	is_builtin(char *cmd)
{
	const char	*builtins[7];
	int			i;

	builtins[0] = "cd";
	builtins[1] = "exit";
	builtins[2] = "env";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "echo";
	builtins[6] = NULL;

	i = 0;
	while (builtins[i])
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
/*
char *ft_strdup(const char *s)
{
	char *dup;
	
	dup = safe_malloc(strlen(s) + 1);
	strcpy(dup, s);
	return (dup);
}
*/

char *ft_strdup(const char *s);

void init_tab (t_msh_cmd *cmd)
{
	cmd->argc = 0;
	cmd->argv = safe_malloc(sizeof(char *) * MAX_TOKENS);
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->append_out = NULL;
	cmd->here_doc = NULL;
}

void init_command(char *line, t_msh_cmd *cmd)
{
	char **tokens;
	int i;

	tokens = tokenize_line(line);
	i = 0;

	init_tab(cmd);
	while (tokens[i]) 
	{
		if (strcmp(tokens[i], "<") == 0 && tokens[i + 1])
			cmd->redir_in = ft_strdup(tokens[++i]);
		else if (strcmp(tokens[i], ">") == 0 && tokens[i + 1])
			cmd->redir_out = ft_strdup(tokens[++i]);
		else if (strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
			cmd->append_out = ft_strdup(tokens[++i]);
		else if (strcmp(tokens[i], "<<") == 0 && tokens[i + 1])
			cmd->here_doc = ft_strdup(tokens[++i]);
		else
			cmd->argv[cmd->argc++] = ft_strdup(tokens[i]);
		i++;
	}
	cmd->argv[cmd->argc] = NULL;
	cmd->name = (cmd->argc > 0) ? cmd->argv[0] : NULL;
	cmd->is_builtin = is_builtin(cmd->name);
	free_tokens(tokens);
}

char *shell_read_line(void)
{
    char *buf;
    size_t bufsize;
    char cwd[BUFSIZ];

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

/*
int main(void)
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

        cmd_count = parse_pipeline(line, &cmds);
        p(G"\nNombre de commandes détectées : %d\n"RST, cmd_count);

        for (int i = 0; i < cmd_count; i++) 
		{
            t_msh_cmd cmd = cmds[i];
            p(C"\n--- Commande #%d ---\n"RST, i + 1);
            p("Nom       : %s\n", cmd.name ? cmd.name : "(null)");
            p("Builtin   : %s\n", cmd.is_builtin ? "oui" : "non");

            p("Arguments :\n");
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
}*/