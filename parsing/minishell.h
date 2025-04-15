/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:39:16 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/15 16:48:38 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdint.h>
# include <fcntl.h>

// Couleur
#define Y "\033[1;33m" // Yellow
#define G "\033[1;32m" // Green
#define C "\033[1;36m" // Cyan
#define RED "\033[1;31m"
#define RST "\033[0m" // Reset

#define p(...) printf(__VA_ARGS__)
#define DEL "\n\t \v\f\r"
#define SHELL_J 0

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

// Function prototypes
void *safe_malloc(size_t size);
void Getcwd(char *buf, size_t size);
void printbanner(void);
void Execvp(const char *file, char *const argv[]);
int is_operator(char c);
char *substr(const char *src, int start, int end);
char **tokenize_line(const char *line);
void free_segments(char **segments);
char	**split_pipeline(const char *line);
int parse_pipeline(char *line, t_msh_cmd **cmds_out);
void init_command(char *line, t_msh_cmd *cmd);
void free_command(t_msh_cmd *cmd);
void free_tokens(char **tokens);
void	shell_exec(t_msh_cmd *cmds, int cmd_count);
void	exit_with_error(const char *msg);
void	handle_redirs(t_msh_cmd cmd);
void	execute_child(t_msh_cmd *cmds, int i, int in_fd, int pipefds[2]);

typedef struct s_builtin
{
    const char *builtin_name;
    int (*foo)(char **);
}       t_builtin;

#endif
