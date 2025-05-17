/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:27:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 16:22:40 by axlleres         ###   ########.fr       */
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
		cmds_len = parse_pipeline(input, &cmds, &ctx);
		free(input);
		msh_exec(&ctx, cmds, cmds_len);
		ctx.last_status = ctx.last_status % 256;
	}
	rl_clear_history();
	msh_free_ctx(&ctx);
	return (0);
}
