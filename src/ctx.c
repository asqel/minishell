/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:36:07 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/01 14:29:45 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_free_ctx(t_msh_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->env_len)
	{
		free(ctx->env[i].name);
		free(ctx->env[i].value);
	}
	free(ctx->env);
	//free(ctx->old_pwd);
	//free(ctx->pwd);
}

void	msh_init_ctx(t_msh_ctx *ctx)
{
	ctx->env = NULL;
	ctx->env_len = 0;
	//ctx->old_pwd = malloc()
}
