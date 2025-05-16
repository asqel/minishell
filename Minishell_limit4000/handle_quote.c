/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:24:48 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/16 18:48:00 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*append_token_part(char *buffer, const char *line, int start, int len)
{
	char	*part;
	char	*joined;

	part = ft_substr(line, start, len);
	if (!part)
		return (NULL);
	joined = ft_strjoin(buffer, part);
	free(buffer);
	free(part);
	return (joined);
}

int	handle_quoted_part(const char *line, int *i, char **buffer)
{
	char	quote;
	int		start;

	quote = line[(*i)++];
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	*buffer = append_token_part(*buffer, line, start, *i - start);
	if (!*buffer)
		return (-1);
	if (line[*i] == quote)
		(*i)++;
	return (0);
}

int	handle_unquoted_part(const char *line, int *i, char **buffer)
{
	int	start;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '\'' && line[*i] != '"' && !is_operator(line[*i]))
		(*i)++;
	*buffer = append_token_part(*buffer, line, start, *i - start);
	if (!*buffer)
		return (-1);
	return (0);
}

int	handle_word_combined(const char *line, char **tokens, int *i, int k)
{
	char	*buffer;

	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (-1);
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& !is_operator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (handle_quoted_part(line, i, &buffer) == -1)
				return (-1);
		}
		else
		{
			if (handle_unquoted_part(line, i, &buffer) == -1)
				return (-1);
		}
	}
	tokens[k] = buffer;
	return (k + 1);
}
