/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:27:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/06 19:29:51 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>


void disable_ctrl_backslash() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        exit(1);
    }

    // Désactiver Ctrl+\ en mettant le caractère VQUIT à 0
    term.c_cc[VQUIT] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("tcsetattr");
        exit(1);
    }
}

int	main()
{

	disable_ctrl_backslash();
	rl_catch_signals = 0;
	while (1)
	{
		char	*input = readline("prompt> ");
		if (!input)
			break ;
		if (g_last_signal != 0)
		{
			printf("Signal %d received\n", g_last_signal);
			g_last_signal = 0;
		}
		printf("You entered: %s\n", input);

		free(input);
	}
	return (0);
}
