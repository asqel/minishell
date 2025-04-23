/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:27:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/23 15:41:48 by axlleres         ###   ########.fr       */
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
	(void)argc;
	(void)argv;
	t_msh_ctx ctx;
	msh_init(env, &ctx);
	rl_catch_signals = 0;
	int last_exec_state = 0;
	char prompt[1024];
	while (1)
	{
		char *input = NULL;
		if (last_exec_state == 0)
		{
			getcwd(prompt, 1000);
			ft_strcat(prompt, "$ ");
			input = readline(prompt);
		}
		else
			input = readline("");
		if (!input)
			break;
		if (g_last_signal != 0)
		{
			printf("Signal %d received\n", g_last_signal);
			g_last_signal = 0;
		}
		add_history(input);
		t_msh_cmd *cmds = NULL;
		int cmd_len = parse_pipeline(input, &cmds);
		if (cmd_len == 1) {
			cmds[0].path = msh_find_cmd(cmds[0].argv[0], &cmds[0].is_builtin, &ctx);
			last_exec_state = msh_exec_cmd_single(&ctx, &cmds[0]);
		}

		free(input);
	}
	return (0);
}
