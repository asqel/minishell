/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:32:13 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/01 13:34:20 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include "minishell.h"


int g_last_signal = 0;

int is_executing(int set_val, int val);

void msh_sig_handler(int signum)
{
	g_last_signal = signum;
	if (signum == SIGINT && !is_executing(0, 0))
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
