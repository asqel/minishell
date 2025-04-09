/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:31:27 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/09 15:19:57 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdint.h>

void	ft_bzero(void *ptr, size_t len)
{
	uint8_t *data;

	data = (uint8_t *)ptr;
	while (len > 0)
		data[--len] = 0;
}
