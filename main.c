/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:27:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/01 19:23:31 by axlleres         ###   ########.fr       */
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

void ft_memset(void *ptr, int c, int len)
{
	char *p;

	p = (char *)ptr;
	while (--len >= 0)
		p[len] = (unsigned char)c;
}

int ft_strstart(char *big, char *little)
{
	int big_len;
	int little_len;

	little_len = ft_strlen(little);
	big_len = ft_strlen(big);
	if (little_len > big_len)
		return (0);
	while (*little != '\0')
		if (*(little++) != *(big++))
			return (0);
	return (1);
}

void *ft_calloc(size_t size, size_t n)
{
	char *res;

	res = malloc(size * n);
	ft_memset(res, 0, size * n);
	return res;
}

void ft_str_rm_start(char *str, int start_len)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = start_len - 1;
	while (++i < len)
		str[i - start_len] = str[i];
	str[i - start_len] = '\0';
}

void ft_strcat_start(char *str, char *start)
{
	int i;
	int len;
	int start_len;

	start_len = ft_strlen(start);
	len = ft_strlen(str);
	i = -1;
	while (++i < len)
		str[start_len + len - 1 - i] = str[len - 1 - i];
	str[start_len + len] = '\0';
	memcpy(str, start, start_len);
}

void msh_reduce_path(char *path, t_msh_ctx *ctx)
{
	char	*home;
	int		home_len;

	home = msh_get_env(ctx, "HOME", NULL);
	if (home == NULL)
		return ;
	if (!ft_strstart(path, home))
		return ;
	home_len = ft_strlen(home);
	ft_str_rm_start(path, home_len);
	ft_strcat_start(path, "~");
}

char *get_pretty_prompt(t_msh_ctx *ctx)
{
	char path[1024];
	char *user;
	char *res;

	memset(path, 0, 1024);
	getcwd(path, 1023);
	msh_reduce_path(path, ctx);
	user = msh_get_env(ctx, "USER", NULL);
	if (user == NULL)
	{
		res = ft_calloc(sizeof(char), (ft_strlen(path) + 30));
		ft_strcat(res, "\001\033[01;34m\002");
		ft_strcat(res, path);
		ft_strcat(res, "\001\033[00m\002");
		ft_strcat(res, "$ ");
		return (res);
	}
	res = ft_calloc(sizeof(char), (ft_strlen(path) + ft_strlen(user) + 60));
	ft_strcat(res, "\001\033[01;32m\002");
	ft_strcat(res, user);
	ft_strcat(res, ":");
	ft_strcat(res, "\001\033[01;34m\002");
	ft_strcat(res, path);
	ft_strcat(res, "\001\033[00m\002");
	ft_strcat(res, "$ ");
	return (res);

}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_msh_ctx ctx;
	msh_init(env, &ctx);
	rl_catch_signals = 0;
	int last_exec_state = 0;
	char *prompt;
	while (1)
	{
		char *input = NULL;
		if (last_exec_state == 0)
		{
			prompt = get_pretty_prompt(&ctx);
			input = readline(prompt);
			free(prompt);
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
		for (int i = 0; i < cmd_len; i++)
			cmds[i].path = msh_find_cmd(cmds[i].argv[0], &cmds[i].is_builtin, &ctx);
		if (cmd_len == 1)
			msh_exec_cmd_single(&ctx, &cmds[0]);
		else
			msh_exec_cmd_pipes(&ctx, cmds, cmd_len);
		for (int i = 0; i < cmd_len; i++)
		{
			for (int j = 0; j < cmds[i].argc; j++)
				free(cmds[i].argv[j]);
			free(cmds[i].argv);
			free(cmds[i].redir_in);
			free(cmds[i].redir_out);
			free(cmds[i].append_out);
			free(cmds[i].here_doc);
			free(cmds[i].path);
		}
		free(cmds);
		free(input);
	}
	rl_clear_history();
	msh_free_ctx(&ctx);
	return (0);
}
