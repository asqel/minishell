/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:29 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/06 20:48:52 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_last_signal = 0;



// Strings
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

// Errors
void	msh_print_error(char *str, int exit_code);

// Signals
void	msh_sig_handler(int signum);


#endif