/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:29 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/15 15:56:00 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdint.h>
#include <stdlib.h>

extern int g_last_signal;

typedef struct
{
	char	*path;
	char	**argv;
	int		argc;
	char	*name;
	uint8_t	is_builtin;
	char	*redir_out; // >
	char	*redir_in; // <
	char	*here_doc; // <<
	char	*append_out; // >>
	int 	type_out;
	int 	type_in;
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
	int				last_status;
} t_msh_ctx;

typedef struct
{
	int			pipes[2];
	int			heredoc_pipes[2];
	t_msh_cmd	*cmd;
	t_msh_ctx	*ctx;
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
void	ft_memcpy(void *dest, const void *src, int len);
int		ft_strchr(char *str, int c);

// Errors
void	msh_print_error(char *str, int exit_code);
void	msh_free(void **ptr);

// Signals
void	msh_sig_handler(int signum);

// exec
void	msh_exec_cmd_single(t_msh_ctx *ctx, t_msh_cmd *cmd);
void	msh_exec_cmd_pipes(t_msh_ctx *ctx, t_msh_cmd *cmd, int cmd_len);
void	msh_exec(t_msh_ctx *ctx, t_msh_cmd *cmds, int cmds_len);
char	*msh_find_cmd(char *name, uint8_t *is_builtin, t_msh_ctx *ctx);

void	msh_init(char **env, t_msh_ctx *ctx);
void	msh_init_ctx(t_msh_ctx *ctx);

char *msh_get_env(t_msh_ctx *ctx, char *name, int *exists);

// builtins
int	msh_blt_cd(int argc, char **argv, t_msh_ctx *ctx);
int msh_blt_echo(int argc, char **argv, t_msh_ctx *ctx);

void	msh_free_ctx(t_msh_ctx *ctx);

void print_error_exit(char *str, int exit_code);

char	*msh_get_cwd(void);
void ft_memset(void *ptr, int c, int len);
void *ft_calloc(size_t size, size_t n);
int	ft_strstart(char *big, char *little);
char *msh_get_prompt(t_msh_ctx *ctx);
void ft_strcat_start(char *str, char *start);
char	*msh_get_input(t_msh_ctx *ctx);
void	msh_free_cmds(t_msh_cmd *cmds, int cmds_len);
void print_error(char *str);
void msh_get_heredoc(t_msh_cmd *cmd);
int msh_blt_pwd(int argc, char **argv, t_msh_ctx *ctx);
char *ft_itoa(int n);

int	msh_redir_in(t_msh_cmd *cmd);
int msh_redir_out(t_msh_cmd *cmd);
int msh_redir_append(t_msh_cmd *cmd);

void print_error_acces(char *filename);

int		msh_is_executable(char *path);
void	print_error_found(char *filename);


#endif
