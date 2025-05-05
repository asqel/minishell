/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:40:11 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/05 19:42:02 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

char	*msh_get_cwd(void)
{
	char	*path;
	int		path_len;

	path_len = 500;
	while (path_len < 2000 || path == NULL)
	{
		path = malloc(sizeof(char) * path_len);
		if (path == NULL)
			return (NULL);
		if (getcwd(path, path_len) != NULL)
			return (path);
		free(path);
		path = NULL;
		path_len += 250;
	}
	return (path);
}
