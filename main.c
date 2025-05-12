/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:27:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/07 20:34:57 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int parse_pipeline(char *text, t_msh_cmd **lst);

int	main(int argc, char **argv, char **env)
{
	t_msh_ctx	ctx;
	char		*input;
	t_msh_cmd	*cmds;
	int			cmds_len;

	(void)argc;
	(void)argv;
	msh_init(env, &ctx);
	while (1)
	{
		input = msh_get_input(&ctx);
		if (!input)
			break;
		cmds_len = parse_pipeline(input, &cmds);
		free(input);
		printf("%p %p %p %p %d %d\n", cmds[0].append_out, cmds[0].here_doc, cmds[0].redir_in, cmds[0].redir_out, cmds[0].type_out, cmds[0].type_in);
		msh_exec(&ctx, cmds, cmds_len);
	}
	rl_clear_history();
	msh_free_ctx(&ctx);
	return (0);
}
