/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 02:29:13 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/16 02:41:51 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_segments(const char *line)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while ('\0' != line[i])
	{
		if ('|' == line[i])
			res++;
		else if ('\'' == line[i])
		{
			i++;
			while ('\'' != line[i] && '\0' != line[i])
				i++;
		}
		else if ('"' == line[i])
		{
			i++;
			while ('"' != line[i] && '\0' != line[i])
				i++;
		}
		if ('\0' != line[i])
			i++;
	}
	return (res);
}