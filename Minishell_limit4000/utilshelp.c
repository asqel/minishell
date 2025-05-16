/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilshelp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:56:44 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/16 18:14:04 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*ft_substr(const char *src, int start, int end)
{
	int		len;
	char	*s;
	int		i;

	len = end - start;
	s = malloc(len + 1);
	i = 0;
	while (start < end)
		s[i++] = src[start++];
	s[i] = '\0';
	return (s);
} */

int is_whitespace(const char *line)
{
    while (*line)
	{
        if (*line != ' ' && *line != '\t' && *line != '\n' &&
            *line != '\r' && *line != '\v' && *line != '\f')
            return (0);
        line++;
    }
    return (1);
}
