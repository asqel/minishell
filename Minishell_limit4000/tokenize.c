/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:57:50 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/16 15:59:13 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_TOKENS 4000

static int	skip_space(const char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static int	handle_quotes(const char *line, char **tokens, int *i, int k)
{
	char	quote;
	int		start;

	quote = line[(*i)++];
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	tokens[k++] = ft_substr(line, start, *i);
	if (line[*i])
		(*i)++;
	return (k);
}

static int	handle_operator(const char *line, char **tokens, int *i, int k)
{
	if ((line[*i] == '>' && line[*i + 1] == '>') || (line[*i] == '<' && line[*i
				+ 1] == '<'))
	{
		tokens[k++] = ft_substr(line, *i, *i + 2);
		*i += 2;
	}
	else
	{
		tokens[k++] = ft_substr(line, *i, *i + 1);
		(*i)++;
	}
	return (k);
}

static int	handle_word(const char *line, char **tokens, int *i, int k)
{
	int	start;

	start = *i;
	while (line[*i] && !(line[*i] == ' ' || line[*i] == '\t'
			|| is_operator(line[*i])))
		(*i)++;
	tokens[k++] = ft_substr(line, start, *i);
	return (k);
}

char	**tokenize_line(const char *line)
{
	char	**tokens;
	int		i;
	int		k;

	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	i = 0;
	k = 0;
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		i = skip_space(line, i);
		if (line[i] == '\0')
			break ;
		if (line[i] == '\'' || line[i] == '"')
			k = handle_quotes(line, tokens, &i, k);
		else if (is_operator(line[i]))
			k = handle_operator(line, tokens, &i, k);
		else
			k = handle_word(line, tokens, &i, k);
	}
	tokens[k] = NULL;
	printf("tokens: %p\n", tokens);
	printf("tokens[0]: %p\n", tokens[0]);
	return (tokens);
}
