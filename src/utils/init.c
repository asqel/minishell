/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:26:00 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/05 20:19:10 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


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

char *get_env_key(char *env_var) {
    int	i;

	i = 0;
	while (env_var[i] != '=' && env_var[i] != '\0')
		i++;
	if (env_var[i] == '\0')
		return ft_strdup(env_var);
	return sub_str(env_var, 0, i);
}

char *get_env_val(char *env_var) {
	int	i;

	i = 0;
	while (env_var[i] != '=' && env_var[i] != '\0')
		i++;
	if (env_var[i] == '\0')
		return (NULL);
	return ft_strdup(&env_var[i + 1]);
}

void parse_env(char **env, t_msh_ctx *ctx)
{
	int env_len;
	int i;

	if (env == NULL)
		return ;
	env_len = 0;
	while (env[env_len] != NULL)
		env_len++;
	ctx->env_len = env_len;
	ctx->env = malloc(sizeof(t_msh_env_var_t) * env_len);
	if (ctx->env == NULL)
		print_error_exit("malloc", 1);
	i = 0;
	while (i < ctx->env_len)
	{
		ctx->env[i].name = get_env_key(env[i]);
		if (ctx->env[i].name == NULL)
		{
			ctx->env_len = i;
			msh_free_ctx(ctx);
			print_error_exit("malloc", 1);
		}
		ctx->env[i].value = get_env_val(env[i]);
		i++;
	}
}

void	msh_init(char **env, t_msh_ctx *ctx)
{
	//if (msh_disable_sigquit() != 0) // !TODO: reenable this
	//	exit(1);
	if (signal(SIGINT, &msh_sig_handler) == SIG_ERR)
		exit(1);
	msh_init_ctx(ctx);
	parse_env(env, ctx);
	rl_catch_signals = 0;
}