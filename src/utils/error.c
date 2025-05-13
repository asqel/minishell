/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:31:44 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/12 18:28:29 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

void print_error_exit(char *str, int exit_code)
{
	if (str == NULL)
		exit(exit_code);
	write(STDERR_FILENO, "Error:\n\t", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	exit(exit_code);
}

void print_error(char *str)
{
	if (str == NULL)
		return ;
	write(STDERR_FILENO, "Error:\n\t", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

void print_error_acces(char *filename)
{
	write(STDERR_FILENO, "Error:\n\t", 8);
	write(STDERR_FILENO, "cannot access ", 14);
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, "\n", 1);
}