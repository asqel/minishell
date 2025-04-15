/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilshelp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:56:44 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/15 16:58:17 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t Wait(int *status)
{
    pid_t result;
    
    if (!status)
    {
        fprintf(stderr, RED"Wait : status argument required\n"RST);
        return (-1);
    }
    result = wait(status);
    if (result == -1)
        perror(RED"Wait failed"RST);
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    return (result);
}

void Getcwd(char *buf, size_t size)
{
    if (NULL == getcwd(buf, size))
        perror(RED"getcwd FAILED"RST);
}
char *substr(const char *src, int start, int end)
{
	int len = end - start;
	char *s = malloc(len + 1);
	int i = 0;
	while (start < end)
		s[i++] = src[start++];
	s[i] = '\0';
	return s;
}

int is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}
