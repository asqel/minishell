/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:33:28 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/08 13:33:50 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	msh_print_error(char *str, int exit_code)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	if (exit_code != -1)
		exit(exit_code);
}

void	msh_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
