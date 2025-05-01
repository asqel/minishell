/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:30:31 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/30 19:06:54 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_segments(char **segments)
{
	int i;
	
	i = 0;
	while (segments[i])
		free(segments[i++]);
	free(segments);
}

void free_command(t_msh_cmd *cmd)
{
	int i;

	i = 0;
    if (!cmd) 
		return;
    while (i < cmd->argc)
	{
        free(cmd->argv[i]);
		i++;
	}
    free(cmd->argv);
    if (cmd->redir_in) free(cmd->redir_in);
    if (cmd->redir_out) free(cmd->redir_out);
    if (cmd->append_out) free(cmd->append_out);
    if (cmd->here_doc) free(cmd->here_doc);
}
void free_tokens(char **tokens)
{
	int i;
	
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
void	free_split(char **array)
{
	int i;
	
	i = 0;
	if (!array)
		return;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
void	free_tab(char **tab, size_t allocated)
{
	size_t	i;

	i = 0;
	while (i < allocated)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
	return ;
}
