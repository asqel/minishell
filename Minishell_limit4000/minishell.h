/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:39:16 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/07 20:31:13 by axlleres         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>


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
	char *name;
	char *value; // if NULL no =
} t_msh_env_var_t;

typedef struct
{
	t_msh_env_var_t	*env;
	int				env_len;
	int				last_status;
} t_msh_ctx;

//builtin_help
int	is_builtin(char *cmd);
void run_builtin(t_msh_cmd *cmd);

//builtin
int execute_builtin(char *cmd, char **args);
void cmd_echo(char **argv);
void cmd_cd(char **argv);
void cmd_pwd(void);
void cmd_exit(char **argv);

//env
void cmd_env(void);
char *get_env_variable(const char *name);
int set_env_variable(const char *name, const char *value);
int unset_env_variable(const char *name);
void cmd_export(char **argv);
void cmd_unset(char **argv);

//free
void free_segments(char **segments);
void free_command(t_msh_cmd *cmd);
void free_tokens(char **tokens);
void	free_split(char **array);
void	free_tab(char **tab, size_t allocated);

//ft_split
char	**ft_split(char const *s, char c);
char *join_path(const char *dir, const char *cmd);

//init_help
void msh_get_heredoc(t_msh_cmd *cmd);
void print_error(char *str);
int	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
//init
void set_redir_1(char **redir, const char *value, t_msh_cmd *cmd, int is_in);
void set_redir_2(char **redir, const char *value, t_msh_cmd *cmd, int is_in);
void set_redir (char *line, t_msh_cmd *cmd);
void init_command(char *line, t_msh_cmd *cmd);
void init_tab (t_msh_cmd *cmd);

//minishell
void init_tab (t_msh_cmd *cmd);
void init_command(char *line, t_msh_cmd *cmd);
char *shell_read_line(void);
void	try_exec_in_path(t_msh_cmd *cmd);
//parsing_help
int	ft_isspace(char c);
int only_spaces(const char *line);
void	update_quote(char c, char *quote);
int	skip_spaces(const char *line, int i);

//parsing_pipe
char	**split_pipeline(const char *line);
int parse_pipeline(char *line, t_msh_cmd **cmds_out);

//shell_exec
void	shell_exec(t_msh_cmd *cmds, int cmd_count);
void	execute_child(t_msh_cmd *cmds, int i, int in_fd, int pipefds[2]);
void	handle_redirs(t_msh_cmd cmd);
void	exit_with_error(const char *msg);
//tokenize
char **tokenize_line(const char *line);

//utils
void printbanner(void);
void *safe_malloc(size_t size, int nb);
pid_t Fork(void);
void Execvp(const char *file, char *const argv[]);

//utilshelp
pid_t Wait(int *status);
void Getcwd(char *buf, size_t size);
char *ft_substr(const char *src, int start, int end);
int is_operator(char c);
char *read_heredoc(const char *delimiter);
char *ft_strdup(const char *s);


typedef struct s_builtin
{
    const char *builtin_name;
    int (*foo)(char **);
}       t_builtin;

#endif
