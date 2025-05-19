/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:28:25 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/19 17:02:53 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_op(char *tok)
{
	return (tok[ft_strlen(tok) + 1] != '\0');
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
		if (!strcmp(tokens[i], "<") && tokens[i + 1] && is_op(tokens[i]))
			set_redir_1(&cmd->redir_in, tokens[++i], cmd, 1);
		else if (!strcmp(tokens[i], ">") && tokens[i + 1] && is_op(tokens[i]))
			set_redir_1(&cmd->redir_out, tokens[++i], cmd, 0);
		else if (!strcmp(tokens[i], ">>") && tokens[i + 1] && is_op(tokens[i]))
			set_redir_2(tokens[++i], cmd, 0, NULL);
		else if (!strcmp(tokens[i], "<<") && tokens[i + 1] && is_op(tokens[i]))
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
