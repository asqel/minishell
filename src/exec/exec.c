/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asqel <asqel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:21:27 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/23 20:15:01 by asqel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	is_executing(int set_val, int val)
{
	static int	executing = 0;

	if (set_val)
		executing = val;
	return (executing);
}

void	msh_exec(t_msh_ctx *ctx, t_msh_cmd *cmds, int cmds_len)
{
	int	i;

	i = -1;
	while (++i < cmds_len)
	{
		cmds[i].argv[cmds[i].argc] = NULL;
		if (cmds[i].name == NULL)
		{
			print_error("minishell: syntax error near '|'\n");
			msh_free_cmds(cmds, cmds_len);
			ctx->last_status = 2;
			return ;
		}
	}
	if (cmds_len == 0)
		return ;
	if (ctx->heredoc_canceled == 1)
		ctx->heredoc_canceled = 0;
	if (cmds[0].argc == -1)
		return (msh_free_cmds(cmds, cmds_len));
	else if (cmds_len == 1)
		msh_exec_cmd_single(ctx, &cmds[0]);
	else if (cmds_len > 1)
		msh_exec_cmd_pipes(ctx, cmds, cmds_len);
	msh_free_cmds(cmds, cmds_len);
}

int	msh_launch_file(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	char	**env;
	int		i;

	if (msh_is_executable(cmd->path))
	{
		env = msh_build_env(ctx);
		execve(
			cmd->path,
			cmd->argv,
			env);
		perror("execve");
		if (env == NULL)
			return (0);
		i = 0;
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
		return (0);
	}
	return (1);
}
