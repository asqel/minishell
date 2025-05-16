/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:29 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/16 16:28:17 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

extern int g_last_signal;

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

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
	t_env	*env;
	int		last_status;
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



// builtin
int					execute_builtin(char *cmd, char **args);
t_env   *env_init(char **envp);
void    env_free(t_env *env);

// Accès
char    *env_get(t_env *env, const char *key);
void    env_set(t_env **env, const char *key, const char *value);
void    env_unset(t_env **env, const char *key);
char    **env_to_tab(t_env *env);

// Builtins
void    builtin_env(t_env *env);
void    builtin_export(t_env **env, char **args);
void    builtin_unset(t_env **env, char **args);

// Utils
int     is_valid_key(const char *key);
//------------------------------------------------------------
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
char 	*ft_strndup(const char *s, size_t n);

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
int msh_blt_echo(int argc, char **argv);
int msh_blt_exit(t_msh_cmd *cmd, t_msh_ctx *ctx, int old_fd);

void	msh_free_ctx(t_msh_ctx *ctx);

void print_error_exit(char *str, int exit_code);

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
void msh_set_env(t_msh_ctx *ctx, char *name, char *value);
int	ft_atoi(char *text, int64_t *res);

void msh_blt_exit2(t_msh_process *processes, int cmd_len, t_msh_ctx *ctx, int i);
//input

char	*msh_get_input(t_msh_ctx *ctx);
char *replace_var(char *input, t_msh_ctx *ctx);
void replace_append_var(char *input, int *i, char *res, t_msh_ctx *ctx, int *k);
void replace_append_quote(char *input, int *i, char *res, int *k);
int get_input_size(char *input, t_msh_ctx *ctx);
int is_var_sep(char c);
char *get_var_name(char *input);
int get_var_val_len(char *input, t_msh_ctx *ctx);
int verif_line(char *input);

#endif
