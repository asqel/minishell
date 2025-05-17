/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:03:29 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 21:16:37 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void token_count_squoted(char *line, int *i, int *res, int *last_token_op)
{
	(*i)++;
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
	{
		*res = -1;
		return ;
	}
	(*i)++;
	(*last_token_op) = 0;
}

static void token_count_dquoted(char *line, int *i, int *res, int *last_token_op)
{
	(*i)++;
	while (line[*i] != '\"' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
	{
		*res = -1;
		return ;
	}
	(*i)++;
	(*last_token_op) = 0;
}

static void token_count_redir(char *line, int *i, int *res, int *last_token_op)
{
	(*res)++;
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '>')
		{
			(*res) = -1;
			print_error("minishell: missing redirection\n");
		}
		else if (line[*i] == '<')
			(*i)++;
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '<')
		{
			(*res) = -1;
			print_error("minishell: missing redirection\n");
		}
		else if (line[*i] == '>')
			(*i)++;
	}
	(*last_token_op) = 1;
}

static void token_count_word(char *line, int *i, int *res, int *last_token_op)
{
	(*res)++;
	while (!ft_is_space(line[*i]) && line[*i] != '\0' && line[*i] != '\"'
		&& line[*i] != '\'' && line[*i] != '<' && line[*i] != '>')
		(*i)++;
	(*last_token_op) = 0;
}

int	token_count(char *line)
{
	int	i;
	int	res;
	int	last_token_op;

	i = 0;
	res = 0;
	last_token_op = 0;
	while (line && line[i] != '\0')
	{
		while (ft_is_space(line[i]))
			i++;
		if (line[i] == '\'')
			token_count_squoted(line, &i, &res, &last_token_op);
		else if (line[i] == '\"')
			token_count_dquoted(line, &i, &res, &last_token_op);
		else if (line[i] == '<' || line[i] == '>')
			token_count_redir(line, &i, &res, &last_token_op);
		else if (line[i] != '\0')
			token_count_word(line, &i, &res, &last_token_op);
		if (res == -1)
			return (-1);
	}
	if (last_token_op == 1)
		return (print_error("minishell: missing redirection\n"), -1);
	return (i);
}

static char	*get_token_squoted(char *line, int *i)
{
	char	*token;
	int		start;
	int		len;

	start = ++(*i);
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (NULL);
	len = *i - start;
	token = ft_substr(line, start, len);
	(*i)++;
	return (token);
}

static char	*get_token_dquoted(char *line, int *i)
{
	char	*token;
	int		start;
	int		len;

	start = ++(*i);
	while (line[*i] != '\"' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (NULL);
	len = *i - start;
	token = ft_substr(line, start, len);
	(*i)++;
	return (token);
}

static char	*get_token_redir(char *line, int *i)
{
	char	*token;
	int		start;
	int		len;

	start = *i;
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
			(*i)++;
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
			(*i)++;
	}
	len = *i - start;
	token = ft_substr(line, start, len);
	return (token);
}

static char	*get_next_token(char *line, int *i)
{
	char	*token;
	int		start;
	int		len;

	if (line[*i] == '\'')
		token = get_token_squoted(line, i);
	else if (line[*i] == '\"')
		token = get_token_dquoted(line, i);
	else if (line[*i] == '<' || line[*i] == '>')
		token = get_token_redir(line, i);
	else
	{
		start = *i;
		while (!ft_is_space(line[*i]) && line[*i] != '\0' && line[*i] != '\"'
			&& line[*i] != '\'' && line[*i] != '<' && line[*i] != '>')
			(*i)++;
		len = *i - start;
		token = ft_substr(line, start, len);
	}
	return (token);
}

static void append_token(char **res, int *res_len, char *line, int *i)
{
	char	*token;
	int		old_i;
	char	*tmp;

	old_i = *i;
	token = get_next_token(line, i);
	if (line[old_i] == '<' || line[old_i] == '>')
	{
		res[(*res_len)++] = token;
		return ;
	}
	if (old_i - 1 >= 0 && !ft_is_space(line[old_i - 1]) && *res_len > 0)
	{
		tmp = res[(*res_len) - 1];
		res[(*res_len) - 1] = ft_strjoin(tmp, token);
		free(tmp);
		free(token);
	}
	else
		res[(*res_len)++] = token;
}

char	**get_tokens(char *line, t_msh_ctx *ctx)
{
	char	**res;
	int		res_len;
	int		i;

	line = replace_var(ft_strdup(line), ctx);
	if (line == NULL)
		return (NULL);
	res_len = token_count(line);
	if (res_len == -1)
	{
		ctx->last_status = 2;
		return (free(line), NULL);
	}
	res = malloc(sizeof(char *) * (res_len + 1));
	res_len = 0;
	i = 0;
	while (line[i] != '\0')
	{
		while (ft_is_space(line[i]))
			i++;
		if (line[i] != '\0')
			append_token(res, &res_len, line, &i);
	}
	res[res_len] = NULL;
	return (free(line), res);
}