/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:32:53 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/06 20:45:52 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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