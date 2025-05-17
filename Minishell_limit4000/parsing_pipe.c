/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:21:59 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/17 16:43:30 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pipe_outside_quotes(const char *line, int i, char quote)
{
	return (line[i] == '|' && quote == 0);
}

static void	save_segment(const char *line, char **segments, int *k, int start,
		int end)
{
	segments[*k] = ft_substr(line, start, end);
	(*k)++;
}

static void	process_pipeline_segment(const char *line, t_pipeline_data *data)
{
	update_quote(line[*data->i], data->quote);
	if (is_pipe_outside_quotes(line, *data->i, *data->quote))
	{
		save_segment(line, data->segments, data->k, *data->start, *data->i);
		(*data->i)++;
		*data->i = skip_spaces(line, *data->i);
		*data->start = *data->i;
	}
	else
		(*data->i)++;
}

char **split_pipeline(const char *line)
{
	t_pipeline_data data;
	char **segments;
	int i;
	int k;
	int start;
	char quote = 0;  // Déclare `quote` comme un char

	i = 0;
	k = 0;
	start = 0;
	segments = safe_malloc(sizeof(char *) * (count_segments(line) + 1));
	data.segments = segments;
	data.i = &i;
	data.k = &k;
	data.start = &start;
	data.quote = &quote;  // Assure-toi que `quote` est un pointeur valide
	while (line[*data.i])
		process_pipeline_segment(line, &data);
	if (*data.start < *data.i)
		save_segment(line, data.segments, data.k, *data.start, *data.i);
	data.segments[*data.k] = NULL;
	return (data.segments);
}

static int	parse_clean_help(t_msh_cmd *cmds, char **segments, int i)
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

static int	parse_error_pipe(char **segments, t_msh_ctx *ctx)
{
	print_error("minshell: syntax error near unexpected token `|'\n");
	ctx->last_status = 2;
	free_segments(segments);
	return (0);
}

int	parse_pipeline(char *line, t_msh_cmd **cmds_out, t_msh_ctx *ctx)
{
	char		**segments;
	int			count;
	int			i;
	t_msh_cmd	*cmds;

	if (line == NULL || *line == '\0' || is_whitespace(line))
		return (0);
	segments = split_pipeline(line);
	count = 0;
	i = 0;
	while (segments[count])
		count++;
	if (count != count_segments(line))
		return (parse_error_pipe(segments, ctx));
	cmds = safe_malloc(sizeof(t_msh_cmd) * count);
	ft_memset(cmds, 0, sizeof(t_msh_cmd) * count);
	while (i < count)
	{
		init_command(segments[i], &cmds[i], ctx);
		if (cmds[i].argv == NULL)
			return (parse_clean_help(cmds, segments, i));
		i++;
	}
	*cmds_out = cmds;
	return (free_segments(segments), count);
}
