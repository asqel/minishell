/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:13:03 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 02:25:25 by axlleres         ###   ########.fr       */
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

	if (input[0] == '?')
		return ft_strdup("?");
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
