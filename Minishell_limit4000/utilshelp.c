/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilshelp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:56:44 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/15 16:06:17 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getcwd(char *buf, size_t size)
{
	if (NULL == getcwd(buf, size))
		perror(RED "getcwd FAILED" RST);
}

char	*ft_substr(const char *src, int start, int end)
{
	int		len;
	char	*s;
	int		i;

	len = end - start;
	s = malloc(len + 1);
	i = 0;
	while (start < end)
		s[i++] = src[start++];
	s[i] = '\0';
	return (s);
}

char	*read_heredoc(const char *delimiter)
{
	char	*line;
	char	*tempfile;
	int		fd;

	tempfile = strdup("/tmp/msh_heredoc_XXXXXX");
	fd = mkstemp(tempfile);
	if (fd == -1)
		exit_with_error("mkstemp");
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	lseek(fd, 0, SEEK_SET);
	close(fd);
	return (tempfile);
}
