/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:21:27 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/12 18:25:38 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

int is_executing(int set_val, int val)
{
	static int executing = 0;
	if (set_val)
		executing = val;
	return executing;
}

void	msh_exec(t_msh_ctx *ctx, t_msh_cmd *cmds, int cmds_len)
{
	int	i;

	i = -1;
	while (++i < cmds_len)
	{
		cmds[i].path = msh_find_cmd(cmds[i].name, &cmds[i].is_builtin, ctx);
		if (cmds[i].path == NULL && !cmds[i].is_builtin)
		{
			msh_free_cmds(cmds, cmds_len);
			print_error("command not found");
			ctx->last_status = 127;
			return ;
		}
	}
	if (cmds_len == 1)
		msh_exec_cmd_single(ctx, &cmds[0]);
	else
		msh_exec_cmd_pipes(ctx, cmds, cmds_len);
	msh_free_cmds(cmds, cmds_len);
}