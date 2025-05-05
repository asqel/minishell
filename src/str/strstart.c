/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:50:51 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/05 19:51:14 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int ft_strstart(char *big, char *little)
{
	int big_len;
	int little_len;

	if (big == NULL || little == NULL)
		return (0);
	little_len = ft_strlen(little);
	big_len = ft_strlen(big);
	if (little_len > big_len)
		return (0);
	while (*little != '\0')
		if (*(little++) != *(big++))
			return (0);
	return (1);
}
