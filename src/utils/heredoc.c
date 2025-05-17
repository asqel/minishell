/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:29:24 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 16:48:18 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static void str_append_line(char **dest, char *src, t_msh_ctx *ctx)
{
	char	*new_str;

	if (src == NULL)
		return ;
	src = replace_var(ft_strdup(src), ctx);
	new_str = malloc(ft_strlen(*dest) + 1 + ft_strlen(src) + 1);
	new_str[0] = '\0';
	if (*dest != NULL)
	{
		ft_strcat(new_str, *dest);
		free(*dest);
		ft_strcat(new_str, "\n");
	}
	ft_strcat(new_str, src);
	*dest = new_str;
	free(src);
	return ;
}

void msh_get_heredoc(t_msh_cmd *cmd, t_msh_ctx *ctx)
{
	char	*input;
	char	*content;

	content = NULL;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			print_error("heredoc: EOF");
			return ;
		}
		if (ft_strcmp(input, cmd->here_doc) == 0)
		{
			free(input);
			break ;
		}
		str_append_line(&content, input, ctx);
		free(input);
	}
	free(cmd->here_doc);
	cmd->here_doc = content;
}
