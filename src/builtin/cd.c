/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:20:17 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/14 15:05:25 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	msh_blt_cd(int argc, char **argv, t_msh_ctx *ctx)
{
	if (argc != 2)
		return (1);
	if (chdir(argv[1]))
	{
		write(STDERR_FILENO, "cd: cannot access ", 18);
		write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
		return (1);
	}
	return (0);
}
