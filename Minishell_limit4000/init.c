/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:28:25 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/18 16:20:15 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir_1(char **redir, const char *value, t_msh_cmd *cmd, int is_in)
{
	free(*redir);
	*redir = ft_strdup(value);
	if (is_in)
		cmd->type_in = 1;
	else
		cmd->type_out = 1;
}

void	set_redir_2(char *value, t_msh_cmd *cmd, int is_in, t_msh_ctx *ctx)
{
	if (is_in)
	{
		free(cmd->here_doc);
		cmd->here_doc = ft_strdup(value);
		cmd->type_in = 2;
		msh_get_heredoc(cmd, ctx);
	}
	else
	{
		cmd->type_out = 2;
		free(cmd->append_out);
		cmd->append_out = ft_strdup(value);
	}
}

void	set_redir(char *line, t_msh_cmd *cmd, t_msh_ctx *ctx)
{
	char	**tokens;
	int		i;

	tokens = get_tokens(line, ctx);
	if (tokens == NULL)
		return ;
	cmd->argv = malloc(sizeof(char *) * (tab_len(tokens) + 1));
	i = 0;
	while (tokens[i])
	{
		if (!strcmp(tokens[i], "<") && tokens[i + 1])
			set_redir_1(&cmd->redir_in, tokens[++i], cmd, 1);
		else if (!strcmp(tokens[i], ">") && tokens[i + 1])
			set_redir_1(&cmd->redir_out, tokens[++i], cmd, 0);
		else if (!strcmp(tokens[i], ">>") && tokens[i + 1])
			set_redir_2(tokens[++i], cmd, 0, NULL);
		else if (!strcmp(tokens[i], "<<") && tokens[i + 1])
			set_redir_2(tokens[++i], cmd, 1, ctx);
		else
			cmd->argv[cmd->argc++] = ft_strdup(tokens[i]);
		i++;
	}
	free_split(tokens);
	return ;
}

void	init_command(char *line, t_msh_cmd *cmd, t_msh_ctx *ctx)
{
	init_tab(cmd);
	set_redir(line, cmd, ctx);
	if (cmd->argv == NULL)
		return ;
	if (cmd->argc > 0)
		cmd->name = cmd->argv[0];
	else
		cmd->name = NULL;
}

void	init_tab(t_msh_cmd *cmd)
{
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->append_out = NULL;
	cmd->here_doc = NULL;
}
