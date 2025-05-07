/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:13:03 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/07 18:42:43 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int is_var_sep(char c)
{
	if (c == ' ' || c == '\t' || c == ';' || c == '|' || c == '&'
		|| c == '<' || c == '>' || c == '=' || c == '\n')
		return (1);
	if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	if (c == '$' || c == '\'' || c == '\"')
		return (1);
	if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']')
		return (1);
	if (c == '\\' || c == '`' || c == '!')
		return (1);
	if (c == '/')
		return (1);
	return (0);
}

char *get_var_name(char *input)
{
	int i;
	char *var_name;

	i = 0;
	while (input[i] != '\0' && !is_var_sep(input[i]))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	if (var_name == NULL)
		return (NULL);
	ft_memcpy(var_name, input, i);
	var_name[i] = '\0';
	return (var_name);
}

int get_var_val_len(char *input, t_msh_ctx *ctx)
{
	char *var_name;
	int res;
	int tmp;
	char *val;

	var_name = get_var_name(&input[1]);
	if (!ft_strcmp(var_name, "?"))
	{
		tmp = ctx->last_status;
		if (tmp == 0)
			res = 1;
		while (tmp > 0)
		{
			tmp /= 10;
			res++;
		}
		free(var_name);
		return (res);
	}
	val = msh_get_env(ctx, var_name, NULL);
	res = ft_strlen(val);
	free(var_name);
	return (res);
}

static int get_input_size(char *input, t_msh_ctx *ctx)
{
	int new_size;
	int i;

	new_size = 0;
	i = -1;
	while (input[++i] != '\0')
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\0' && input[i] != '\'')
			{
				new_size++;
				i++;
			}
			if (input[i] != '\'')
				return (print_error("unclosed quote"), -1);
			i++;
		}
		if (input[i] == '$')
			new_size += get_var_val_len(&input[i], ctx);
		else
			new_size++;
	}
	return (new_size);
}

static void replace_append_quote(char *input, int *i, char *res, int *k)
{
	res[*k] = '\'';
	(*k)++;
	(*i)++;
	while (input[*i] != '\0' && input[*i] != '\'')
	{
		res[*k] = input[*i];
		(*k)++;
		(*i)++;
	}
	res[*k] = '\'';
	(*k)++;
	(*i)++;
}

static void replace_append_var(char *input, int *i, char *res, t_msh_ctx *ctx, int *k)
{
	char	*var_name;
	char	*val;
	int		j;

	(*i)++;
	var_name = get_var_name(&input[*i]);
	if (ft_strcmp(var_name, "?") == 0)
	{
		val = ft_itoa(ctx->last_status);
		j = -1;
		while (val[++j] != '\0')
			res[(*k)++] = val[j];
		free(val);
	}
	else
	{
		val = msh_get_env(ctx, var_name, NULL);
		if (val == NULL)
			val = "";
		j = -1;
		while (val[++j] != '\0')
			res[(*k)++] = val[j];
	}
	(*i) += ft_strlen(var_name);
	free(var_name);
}

char *replace_var(char *input, t_msh_ctx *ctx)
{
	char	*res;
	int		new_size;
	int		i;
	int		k;


	new_size = get_input_size(input, ctx);
	if (new_size == -1)
		return (free(input), NULL);
	res = calloc(sizeof(char), (new_size + 1));
	if (res == NULL)
		return (free(input), NULL);
	i = -1;
	k = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == '\'')
			replace_append_quote(input, &i, res, &k);
		else if (input[i] == '$')
			replace_append_var(input, &i, res, ctx, &k);
		else
			res[k++] = input[i];
	}
	res[k] = '\0';
	free(input);
	return (res);
}

char	*msh_get_input(t_msh_ctx *ctx)
{
	char	*input;
	char	*prompt;

	prompt = msh_get_prompt(ctx);
	if (prompt == NULL)
	{
		msh_free_ctx(ctx);
		print_error_exit("malloc", 1);
	}
	input = readline(prompt);
	if (input == NULL)
	{
		free(prompt);
		return (NULL);
	}
	free(prompt);
	add_history(input);
	input = replace_var(input, ctx);
	if (input == NULL)
		return ft_strdup("");
	return (input);
}
