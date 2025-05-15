/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:28:25 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/15 16:23:53 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_redir_1(char **redir, const char *value, t_msh_cmd *cmd, int is_in)
{
	free(*redir);
	*redir = ft_strdup(value);
	if (is_in)
		cmd->type_in = 1;
	else
		cmd->type_out = 1;
}
void set_redir_2(char **redir, const char *value, t_msh_cmd *cmd, int is_in)
{
	free(*redir);
	*redir = ft_strdup(value);
	if (is_in)
		cmd->type_in = 2;
	else
		cmd->type_out = 2;
}

void	set_redir(char *line, t_msh_cmd *cmd)
{
	char	**tokens;
	int		i;

	tokens = tokenize_line(line);
	i = 0;
	while (tokens[i])
	{
		if (!strcmp(tokens[i], "<") && tokens[i + 1])
			set_redir_1(&cmd->redir_in, tokens[++i], cmd, 1);
		else if (!strcmp(tokens[i], ">") && tokens[i + 1])
			set_redir_1(&cmd->redir_out, tokens[++i], cmd, 0);
		else if (!strcmp(tokens[i], ">>") && tokens[i + 1])
			set_redir_2(&cmd->append_out, tokens[++i], cmd, 0);
		else if (!strcmp(tokens[i], "<<") && tokens[i + 1])
		{
			set_redir_2(&cmd->here_doc, tokens[++i], cmd, 1);
			msh_get_heredoc(cmd);
		}
		else
			cmd->argv[cmd->argc++] = ft_strdup(tokens[i]);
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return ;
}

void	init_command(char *line, t_msh_cmd *cmd)
{
	char	**tokens;
	int		i;

	tokens = tokenize_line(line);
	i = 0;
	init_tab(cmd);
	set_redir(line, cmd);
	cmd->argv[cmd->argc] = NULL;
	if (cmd->argc > 0)
		cmd->name = cmd->argv[0];
	else
		cmd->name = NULL;
	cmd->is_builtin = is_builtin(cmd->name);
	free_tokens(tokens);
}

void	init_tab(t_msh_cmd *cmd)
{
	cmd->argc = 0;
	cmd->argv = safe_malloc(sizeof(char *), 256);
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->append_out = NULL;
	cmd->here_doc = NULL;
}
