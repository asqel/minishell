/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 00:51:39 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/19 00:57:26 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var_heredoc(char **input, char *res, int *k)
{
	int	len;

	res[(*k)++] = '<';
	res[(*k)++] = '<';
	(*input) += 2;
	while (ft_is_space(**input))
		(*input)++;
	if ((*input) == '\0')
		return ;
	len = 0;
	while (1)
	{

	}


}