/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:29:54 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/18 16:30:26 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_clean_help(t_msh_cmd *cmds, char **segments, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(cmds[j].path);
		free(cmds[j].argv);
		free(cmds[j].redir_out);
		free(cmds[j].redir_in);
		free(cmds[j].here_doc);
		j++;
	}
	free_segments(segments);
	free(cmds);
	return (0);
}

int	parse_error_pipe(char **segments, t_msh_ctx *ctx)
{
	print_error("minshell: syntax error near unexpected token `|'\n");
	ctx->last_status = 2;
	free_segments(segments);
	return (0);
}
