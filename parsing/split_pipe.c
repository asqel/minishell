/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:21:59 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/15 16:35:50 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	update_quote(char c, char *quote)
{
	if ((*quote == 0) && (c == '\'' || c == '"'))
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}

static int	is_pipe_outside_quotes(const char *line, int i, char quote)
{
	return (line[i] == '|' && quote == 0);
}

static void	save_segment(const char *line, char **segments, int *k, int start, int end)
{
	segments[*k] = substr(line, start, end);
	(*k)++;
}

static int	skip_spaces(const char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}
static void	process_pipeline_segment(const char *line, char **segments, int *i, int *k, int *start, char *quote)
{
	update_quote(line[*i], quote);
	if (is_pipe_outside_quotes(line, *i, *quote))
	{
		save_segment(line, segments, k, *start, *i);
		(*i)++;
		*i = skip_spaces(line, *i);
		*start = *i;
	}
	else
		(*i)++;
}

char	**split_pipeline(const char *line)
{
	char	**segments;
	int		i;
	int		start;
	int		k;
	char	quote;

	segments = safe_malloc(sizeof(char *) * 256);
	i = 0;
	k = 0;
	start = 0;
	quote = 0;
	while (line[i])
		process_pipeline_segment(line, segments, &i, &k, &start, &quote);
	if (start < i)
		save_segment(line, segments, &k, start, i);
	segments[k] = NULL;
	return (segments);
}
int parse_pipeline(char *line, t_msh_cmd **cmds_out)
{
	char **segments;
	int count;
    int i;

    segments = split_pipeline(line);
    count = 0;
    i = 0;
	while (segments[count])
		count++;
	t_msh_cmd *cmds = safe_malloc(sizeof(t_msh_cmd) * count);

	while (i < count) 
    {
		init_command(segments[i], &cmds[i]);
        i++;
    }
	*cmds_out = cmds;
	free_segments(segments);
	return count;
}
