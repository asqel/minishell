/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:28:25 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/05 17:05:51 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_redir(char **redir, const char *value)
{
	free(*redir);
	*redir = ft_strdup(value);
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
		if (!strcmp(tokens[i], "<") && tokens[i + 1])
			set_redir(&cmd->redir_in, tokens[++i]);
		else if (!strcmp(tokens[i], ">") && tokens[i + 1])
			set_redir(&cmd->redir_out, tokens[++i]);
		else if (!strcmp(tokens[i], ">>") && tokens[i + 1])
			set_redir(&cmd->append_out, tokens[++i]);
		else if (!strcmp(tokens[i], "<<") && tokens[i + 1])
			set_redir(&cmd->here_doc, tokens[++i]);
		else
			cmd->argv[cmd->argc++] = ft_strdup(tokens[i]);
		i++;
	}
	cmd->argv[cmd->argc] = NULL;
	cmd->name = (cmd->argc > 0) ? cmd->argv[0] : NULL;
	cmd->is_builtin = is_builtin(cmd->name);
	free_tokens(tokens);
}
void init_tab (t_msh_cmd *cmd)
{
	cmd->argc = 0;
	cmd->argv = safe_malloc(sizeof(char *), 256);
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->append_out = NULL;
	cmd->here_doc = NULL;
}
