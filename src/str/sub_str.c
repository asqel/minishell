/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:37:37 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/05 19:16:55 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *sub_str(char *str, int start, int end)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (end - start  + 1));
	if (res == NULL)
		return (NULL);
	res[end - start] = '\0';
	i = start - 1;
	while (++i < end)
		res[i - start] = str[i];
	return (res);
}
