/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 00:51:39 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 03:01:44 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_dquote(char **input, char *res, int *k)
{
	res[(*k)++] = '\"';
	(*input)++;
	while (**input != '\0' && **input != '\"')
	{
		res[(*k)++] = **input;
		(*input)++;
	}
	res[(*k)++] = '\"';
	(*input)++;
}

static void	do_squote(char **input, char *res, int *k)
{
	res[(*k)++] = '\'';
	(*input)++;
	while (**input != '\0' && **input != '\'')
	{
		res[(*k)++] = **input;
		(*input)++;
	}
	res[(*k)++] = '\'';
	(*input)++;
}

void	replace_var_heredoc(char **input, char *res, int *k)
{
	res[(*k)++] = '<';
	res[(*k)++] = '<';
	(*input) += 2;
	while (ft_is_space(**input))
	{
		(*input)++;
		res[(*k)++] = ' ';
	}
	if ((**input) == '\0')
		return ;
	while (**input != '\0' && !ft_is_space(**input))
	{
		if (**input == '\"')
			do_dquote(input, res, k);
		else if (**input == '\'')
			do_squote(input, res, k);
		else
		{
			res[(*k)++] = **input;
			(*input)++;
		}
	}
	input--;
}
