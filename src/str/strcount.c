/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcount.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:24:06 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 18:24:43 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcount(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
