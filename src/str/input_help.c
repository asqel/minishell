/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:13:03 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 18:29:34 by axlleres         ###   ########.fr       */
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

void replace_append_var(char *input, int *i, char *res, t_msh_ctx *ctx, int *k)
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
	(*i) += ft_strlen(var_name) - 1;
	free(var_name);
}

char *replace_var(char *input, t_msh_ctx *ctx)
{
	char	*res;
	int		new_size;
	int		i;
	int		k;

	if (ft_strcount(input, '"') % 2 != 0)
		return (free(input),
			print_error("minishell: unclosed quote \"\n"), NULL);
	new_size = get_input_size(input, ctx);
	res = malloc(sizeof(char) + (new_size + 1));
	if (res == NULL || new_size == -1)
		return (free(input), free(res), NULL);
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
