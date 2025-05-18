/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:40:24 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 21:41:59 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_is_valid_name(char *name)
{
	int	i;

	i = -1;
	while (name[++i] != '\0')
	{
		if (!('A' <= name[i] && name[i] <= 'Z') &&
			!('a' <= name[i] && name[i] <= 'z') &&
			!('0' <= name[i] && name[i] <= '9') &&
			!(name[i] == '_'))
		{
			return (0);
		}
	}
	return (1);
}
