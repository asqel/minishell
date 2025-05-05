/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:15:00 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/06 00:25:34 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void ft_strcat_start(char *str, char *start)
{
	int i;
	int len;
	int start_len;

	if (str == NULL || start == NULL)
		return ;
	start_len = ft_strlen(start);
	len = ft_strlen(str);
	i = -1;
	while (++i < len)
		str[start_len + len - 1 - i] = str[len - 1 - i];
	str[start_len + len] = '\0';
	ft_memcpy(str, start, start_len);
}
