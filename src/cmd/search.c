/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:22:18 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/05 19:26:36 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_path(t_msh_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->env_len)
		if (!ft_strcmp(ctx->env[i].name, "PATH"))
			return (ctx->env[i].value);
	return (NULL);
}

char *path_contains(char *path, char *name, int *p_len)
{
	int		n_len;
	char	*cmd_path;

	*p_len = 0;
	while (path[*p_len] != '\0' && path[*p_len] != ':')
		(*p_len)++;
	n_len = ft_strlen(name);
	cmd_path = malloc(sizeof(char)  * (*p_len + 1 + n_len + 1 ));
	if (cmd_path == NULL)
		return (NULL);
	cmd_path[*p_len] = '/';
	ft_memcpy(cmd_path, path, *p_len);
	ft_memcpy(&cmd_path[*p_len + 1], name, n_len + 1);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	return (free(cmd_path), NULL);
}

char	*msh_find_cmd(char *name, uint8_t *is_builtin, t_msh_ctx *ctx)
{
	int i;
	char *path;
	int path_len;
	char *res;

	*is_builtin = 0;
	if (ft_strchr(name, '/') != -1)
		return ft_strdup(name);
	i = 0;
	path = get_path(ctx);
	if (path == NULL)
		return (NULL);
	while (path[i] != '\0')
	{
		res = path_contains(&path[i], name, &path_len);
		if (res != NULL)
			return (res);
		i += path_len;
		if (path[i] == ':')
			i++;
	}
	return NULL;
}
