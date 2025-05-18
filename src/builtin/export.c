/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:31:37 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 21:16:21 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(t_msh_env_var_t *env, int len)
{
	int		i;
	int		k;
	t_msh_env_var_t	tmp;
	int		min;

	i = 0;
	while (i < len - 1)
	{
		min = i;
		k = i + 1;
		while (k < len)
		{
			if (ft_strcmp(env[k].name, env[min].name) < 0)
				min = k;
			k++;
		}
		if (min != i)
		{
			tmp = env[i];
			env[i] = env[min];
			env[min] = tmp;
		}
		i++;
	}
}

static void print_env(t_msh_ctx *ctx)
{
	t_msh_env_var_t	*env;
	int				i;

	env = malloc(sizeof(t_msh_env_var_t) * (ctx->env_len));
	i = -1;
	while (++i < ctx->env_len)
		env[i] = ctx->env[i];
	sort_env(env, ctx->env_len);
	i = -1;
	while (++i < ctx->env_len)
	{
		if (env[i].value != NULL)
			printf("declare -x %s=\"%s\"\n", env[i].name, env[i].value);
		else
			printf("declare -x %s\n", env[i].name);
	}

}

static int	try_add_env(t_msh_ctx *ctx, char *name, char *value)
{
	if (!export_is_valid_name(name))
	{
		print_error("minishell: export: `");
		print_error(name);
		print_error("': not a valid identifier\n");
		return (1);
	}
	msh_set_env(ctx, name, value);
	return (0);
}

int builtin_export(int argc, char **argv, t_msh_ctx *ctx)
{
	int	i;

	if (argc == 1)
		return (print_env(ctx), 0);
	i = 1;
	while (i < argc)
	{
		if (ft_strchr(argv[i], "=") == -1)
			if (try_add_env(ctx, argv[i], NULL))
				return (1);
		i++;
	}
	return (0);
}
