/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:10:31 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/07 18:45:10 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(char *str)
{
	if (str == NULL)
		return ;
	write(STDERR_FILENO, "Error:\n\t", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
}
static void str_append_line(char **dest, char *src)
{
	char	*new_str;

	if (src == NULL)
		return ;
	new_str = calloc(ft_strlen(*dest) + 1, ft_strlen(src) + 1);
	new_str[0] = '\0';
	if (*dest != NULL)
	{
		strcat(new_str, *dest);
		free(*dest);
		strcat(new_str, "\n");
	}
	strcat(new_str, src);
	*dest = new_str;
	return ;
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ('\0' != s1[i] && '\0' != s2[i])
	{
		if (s1[i] != s2[i])
			return ((signed char)s1[i] - (signed char)s2[i]);
		i++;
	}
	return ((signed char)s1[i] - (signed char)s2[i]);

}

int	ft_strlen(const char *str)
{
	int	len;

	if (NULL == str)
		return (0);
	len = 0;
	while ('\0' != str[len])
		len++;
	return (len);
}

void msh_get_heredoc(t_msh_cmd *cmd)
{
	char	*input;
	char	*content;

	content = NULL;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			print_error("heredoc: EOF");
			return ;
		}
		if (ft_strcmp(input, cmd->here_doc) == 0)
		{
			free(input);
			break ;
		}
		str_append_line(&content, input);
		free(input);
	}
	free(cmd->here_doc);
	cmd->here_doc = content;
}