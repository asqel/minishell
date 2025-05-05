/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:29:49 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/01 19:28:43 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char **msh_build_env(t_msh_ctx *ctx)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ctx->env_len + 1));
	res[ctx->env_len] = NULL;
	i = -1;
	while (++i < ctx->env_len)
	{
		if (ctx->env[i].value == NULL)
		{
			res[i] = ft_strdup(ctx->env[i].name);
			continue;
		}
		res[i] = malloc(sizeof(char) * (ft_strlen(ctx->env[i].name) + 1 + ft_strlen(ctx->env[i].value) + 1));
		res[i][0] = '\0';
		ft_strcat(res[i], ctx->env[i].name);
		ft_strcat(res[i], "=");
		ft_strcat(res[i], ctx->env[i].value);
	}
	return (res);
}

// exists can be NULL
// doesnt return a copy
char *msh_get_env(t_msh_ctx *ctx, char *name, int *exists)
{
	int	i;

	i = -1;
	if (exists)
		*exists = 1;
	while (++i < ctx->env_len)
		if (!ft_strcmp(ctx->env[i].name, name))
			return (ctx->env[i].value);
	if (exists)
		*exists = 1;
	return (NULL);
}

void msh_set_env(t_msh_ctx *ctx, char *name, char *value)
{
	int	i;
	t_msh_env_var_t	*new_env;

	i = -1;
	while (++i < ctx->env_len)
		if (!ft_strcmp(ctx->env[i].name, name))
		{
			free(ctx->env[i].value);
			ctx->env[i].value = ft_strdup(value);
			return ;
		}
	new_env = malloc(sizeof(t_msh_env_var_t) * (ctx->env_len + 1));
	if (!new_env)
		return ;
	new_env[ctx->env_len].name = ft_strdup(name);
	new_env[ctx->env_len].value = ft_strdup(value);
	ctx->env_len++;
	i = -1;
	while (++i < ctx->env_len - 1)
		new_env[i] = ctx->env[i];
	free(ctx->env);
	ctx->env = new_env;
}

void msh_unset_env(t_msh_ctx *ctx, char *name)
{
	int	i;

	i = -1;
	while (++i < ctx->env_len)
		if (!ft_strcmp(ctx->env[i].name, name))
		{
			free(ctx->env[i].name);
			free(ctx->env[i].value);
			while (i < ctx->env_len - 1)
			{
				ctx->env[i] = ctx->env[i + 1];
				i++;
			}
			ctx->env_len--;
			return ;
		}
}
