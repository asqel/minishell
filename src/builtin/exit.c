/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:12:58 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/15 20:11:34 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdint.h>

static int	no_arg(t_msh_cmd *cmd, t_msh_ctx *ctx, int old_fd)
{
	write(STDERR_FILENO, "exit\n", 5);
	close(old_fd);
	msh_free_cmds(cmd, 1);
	msh_free_ctx(ctx);
	rl_clear_history();
	exit(0);
}

static int	one_arg(t_msh_cmd *cmd, t_msh_ctx *ctx, int old_fd)
{

}

int msh_blt_exit(t_msh_cmd *cmd, t_msh_ctx *ctx, int old_fd)
{
	int		is_int;
	int64_t	exit_code;

	if (cmd->argc == 1)
		return (no_arg(cmd, ctx, old_fd));
	else if (cmd->argc == 2)
	{
		is_int = !ft_atoi(cmd->argv[1], &exit_code);
		rl_clear_history();
		if (!is_int)
		{
			write(STDERR_FILENO, "minishell: exit: ", 20);
			write(STDERR_FILENO, cmd->argv[1], ft_strlen(cmd->argv[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 27);
			exit_code = 2;
		}
		if (is_int)
			write(STDERR_FILENO, "exit\n", 5);
		close(old_fd);
		msh_free_cmds(cmd, 1);
		msh_free_ctx(ctx);
		exit(exit_code % 256);
	}
	write(STDERR_FILENO, "exit\nminishell: exit: too many arguments\n", 41);
	return (1);
}