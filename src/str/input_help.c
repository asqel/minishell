/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:13:03 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 21:37:13 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int get_input_size(char *input, t_msh_ctx *ctx)
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
				return (print_error("minishell: unclosed quote \'\n"), -1);
			i++;
		}
		if (input[i] == '$')
			new_size += get_var_val_len(&input[i], ctx);
		else
			new_size++;
	}
	return (new_size);
}

void replace_append_quote(char *input, int *i, char *res, int *k)
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

static void append_text_val(char *res, char *val, int *k, int in_dquote)
{
	int i;

	i = -1;
	while (val[++i] != '\0')
	{
		if ((val[i] == '<' || val[i] == '>') && !in_dquote)
			res[(*k)++] = '"';
		res[(*k)++] = val[i];
		if ((val[i] == '<' || val[i] == '>') && !in_dquote)
			res[(*k)++] = '"';
	}
}

int replace_append_var(char *input, int *i, char *res, t_msh_ctx *ctx, int in_dquote)
{
	char	*var_name;
	char	*val;
	int		k;

	k = 0;
	(*i)++;
	var_name = get_var_name(&input[*i]);
	if (ft_strcmp(var_name, "?") == 0)
	{
		val = ft_itoa(ctx->last_status);
		append_text_val(res, val, &k, in_dquote);
		free(val);
	}
	else
	{
		val = msh_get_env(ctx, var_name, NULL);
		if (val == NULL)
			val = "";
		append_text_val(res, val, &k, in_dquote);
	}
	(*i) += ft_strlen(var_name) - 1;
	free(var_name);
	return (k);
}

void	replace_var_loop(char *input, char *res, t_msh_ctx *ctx)
{
	int		i;
	int		k;
	int		in_dquote;

	i = -1;
	k = 0;
	in_dquote = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == '\'')
			replace_append_quote(input, &i, res, &k);
		else if (input[i] == '\"')
		{
			in_dquote = !in_dquote;
			res[k++] = input[i];
		}
		else if (input[i] == '$')
			k += replace_append_var(input, &i, &res[k], ctx, in_dquote);
		else
			res[k++] = input[i];
	}
	res[k] = '\0';
}

char *replace_var(char *input, t_msh_ctx *ctx)
{
	char	*res;
	int		new_size;

	if (ft_strcount(input, '"') % 2 != 0)
		return (free(input),
			print_error("minishell: unclosed quote \"\n"), NULL);
	new_size = get_input_size(input, ctx);
	res = malloc(sizeof(char) + (new_size + 1));
	if (res == NULL || new_size == -1)
		return (free(input), free(res), NULL);
	replace_var_loop(input, res, ctx);
	return (free(input), res);
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
	if ((input == NULL))
	{
		free(prompt);
		return (NULL);
	}
	free(prompt);
	add_history(input);
	if (input == NULL)
		return ft_strdup("");
	return (input);
}
