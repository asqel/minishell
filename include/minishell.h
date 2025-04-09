/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:29 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/09 18:13:20 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdint.h>
#include <stdlib.h>

extern int g_last_signal;

// Strings
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		msh_array_len(char **array);
char	*ft_strdup(const char *str);
void	ft_strcpy(char *dest, char *src);

// Errors
void	msh_print_error(char *str, int exit_code);
void	msh_free(void **ptr);

// Signals
void	msh_sig_handler(int signum);

void	msh_init(void);

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
	int				env_len

} t_msh_ctx;

#define ERR_CMD_NOT_FOUND 0xF000

#endif