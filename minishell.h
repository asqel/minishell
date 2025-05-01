/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:29 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/01 19:17:56 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdint.h>
#include <stdlib.h>

extern int g_last_signal;

typedef struct
{
	char *path;
	char **argv;
	int argc;
	char *name;
	uint8_t is_builtin;
	char *redir_out; // >
	char *redir_in; // <
	char *here_doc; // <<
	char *append_out; // >>
} t_msh_cmd;

typedef struct
{
	t_msh_cmd	*cmd;
	int len;
} t_msh_cmd_pipes;

typedef struct
{
	char *name;
	char *value; // if NULL no =
} t_msh_env_var_t;

typedef struct
{
	t_msh_env_var_t	*env;
	int				env_len;
	char			*pwd;
	char			*old_pwd;
	int				last_status;
} t_msh_ctx;

typedef struct
{
	int fds[2];
	int pid;
	int status;
	t_msh_cmd *cmd;

} t_msh_process;

// Strings
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		msh_array_len(char **array);
char	*ft_strdup(const char *str);
void	ft_strcpy(char *dest, char *src);
char	**msh_build_env(t_msh_ctx *ctx);
char	*sub_str(char *str, int start, int end);
void	ft_strcat(char *dest, const char *src);
int		ft_strcontains_char(char *str, char c);
void	ft_memcpy(void *dest, const void *src, int len);
// Errors
void	msh_print_error(char *str, int exit_code);
void	msh_free(void **ptr);

// Signals
void	msh_sig_handler(int signum);

// exec
void	msh_exec_cmd_single(t_msh_ctx *ctx, t_msh_cmd *cmd);
void	msh_exec_cmd_pipes(t_msh_ctx *ctx, t_msh_cmd *cmd, int cmd_len);
char	*msh_find_cmd(char *name, uint8_t *is_builtin, t_msh_ctx *ctx);
int		msh_is_file(char *path);

void	msh_init(char **env, t_msh_ctx *ctx);
void	msh_init_ctx(t_msh_ctx *ctx);

char *msh_get_env(t_msh_ctx *ctx, char *name, int *exists);

// builtins
int	msh_blt_cd(int argc, char **argv);

void	msh_free_ctx(t_msh_ctx *ctx);

#endif
