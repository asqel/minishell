/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:26:00 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/06 19:31:59 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termio.h>
#include <unistd.h>

int	msh_disable_sigquit(void)
{
	struct termios	terminal;

	if (tcgetattr(STDIN_FILENO, &terminal) == -1)
		return (1);
	terminal.c_cc[VQUIT] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) == -1)
		return (1);
	signal(SIGQUIT, &msh_sig_handler);
	return (0);
}

void	msh_init(void)
{
	if (msh_disable_sigquit() != 0)
		exit(1);
	signal(SIGINT, &msh_sig_handler);
}