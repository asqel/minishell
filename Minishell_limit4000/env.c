/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:38:26 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/07 21:13:01 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	cmd_env(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

char	*get_env_variable(const char *name)
{
	return (getenv(name));
}

int	set_env_variable(const char *name, const char *value)
{
	return (setenv(name, value, 1));
}

int	unset_env_variable(const char *name)
{
	return (unsetenv(name));
}
