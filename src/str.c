/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:32:53 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/01 19:34:16 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while ('\0' != str[len])
		len++;
	return (len);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ('\0' != s1[i] && '\0' != s2[i])
	{
		if (s1[i] != s2[i])
			return ((signed char)s1[i] - (signed char)s2[i]);
		i++;
	}
	return ((signed char)s1[i] - (signed char)s2[i]);

}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dup;

	if (NULL == str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (NULL == dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while ('\0' != src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

int	ft_strcontains_char(char *str, char c) {
	int	i;

	i = -1;
	while (str[++i]  != '\0')
		if (str[i] == c)
			return (1);
	return (0);
}
