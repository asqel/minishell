/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:57:50 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/15 16:03:13 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

#define MAX_TOKENS 256

static int skip_spaces(const char *line, int i) 
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static int handle_quotes(const char *line, char **tokens, int *i, int k) 
{
	char quote;
	int start;

    quote = line[(*i)++];
    start = *i;
    while (line[*i] && line[*i] != quote)
		(*i)++;
    tokens[k++] = substr(line, start, *i);
	if (line[*i]) (*i)++; // Skip closing quote
	return k;
}

static int handle_operator(const char *line, char **tokens, int *i, int k) 
{
	if ((line[*i] == '>' && line[*i + 1] == '>') ||
		(line[*i] == '<' && line[*i + 1] == '<')) {
		tokens[k++] = substr(line, *i, *i + 2);
		*i += 2;
	} 
    else 
    {
		tokens[k++] = substr(line, *i, *i + 1);
		(*i)++;
	}
	return (k);
}

static int handle_word(const char *line, char **tokens, int *i, int k) 
{
	int start;

    start = *i;
	while (line[*i] && !(line[*i] == ' ' || line[*i] == '\t' || is_operator(line[*i])))
		(*i)++;
	tokens[k++] = substr(line, start, *i);
	return (k);
}

char **tokenize_line(const char *line) 
{
	char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
	int i = 0, k = 0;

	while (line[i]) {
		i = skip_spaces(line, i);
		if (!line[i]) break;

		if (line[i] == '\'' || line[i] == '\"')
			k = handle_quotes(line, tokens, &i, k);
		else if (is_operator(line[i]))
			k = handle_operator(line, tokens, &i, k);
		else
			k = handle_word(line, tokens, &i, k);
	}
	tokens[k] = NULL;
	return tokens;
}
