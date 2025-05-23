/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asqel <asqel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:20:51 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/23 20:15:31 by asqel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_blt_pwd(int argc, char **argv, t_msh_ctx *ctx)
{
	char	*pwd;

	(void)argc;
	(void)argv;
	(void)ctx;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
