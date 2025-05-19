/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:13:03 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/19 14:36:57 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input_size(char *input, t_msh_ctx *ctx)
{
	int	new_size;
	int	i;

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

void	replace_append_quote(char **input, char *res, int *k)
{
	res[*k] = '\'';
	(*k)++;
	(*input)++;
	while (**input != '\0' && **input != '\'')
	{
		res[*k] = **input;
		(*k)++;
		(*input)++;
	}
	res[*k] = '\'';
	(*k)++;
	(*input)++;
}

static void	append_text_val(char *res, char *val, int *k, int in_dquote)
{
	int	i;

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

int	replace_append_var(char **input, char *res, t_msh_ctx *ctx, int in_dquote)
{
	char	*var_name;
	char	*val;
	int		k;

	k = 0;
	(*input)++;
	var_name = get_var_name(*input);
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
	(*input) += ft_strlen(var_name) - 1;
	free(var_name);
	return (k);
}

void	replace_var_loop(char *input, char *res, t_msh_ctx *ctx)
{
	int		k;
	int		in_dquote;

	k = 0;
	in_dquote = 0;
	while (*input != '\0')
	{
		if (*input == '\'' && !in_dquote)
			replace_append_quote(&input, res, &k);
		else if (*input == '\"')
		{
			in_dquote = !in_dquote;
			res[k++] = *input;
		}
		else if (*input == '$')
			k += replace_append_var(&input, &res[k], ctx, in_dquote);
		else if (*input == '<' && *(input + 1) == '<' && !in_dquote)
			replace_var_heredoc(&input, res, &k);
		else
			res[k++] = *input;
		if (*input == '\0')
			break ;
		input++;
	}
	res[k] = '\0';
}
