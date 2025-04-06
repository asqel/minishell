/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:31:44 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/06 20:48:35 by axlleres         ###   ########.fr       */
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