/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:20:51 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/14 15:05:38 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int msh_blt_pwd(int argc, char **argv, t_msh_ctx *ctx)
{
	char	*pwd;

	(void)argc;
	(void)argv;
	pwd = msh_get_cwd();
	if (pwd == NULL)
	{
		print_error("pwd: error getting current directory");
		return (1);
	}
	printf("%s\n", pwd);
	return (0);
}