/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:15 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/05 17:05:33 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void printbanner(void)
{
    p(G"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
    "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"
    "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"
    "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
    "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"RST);
}

void *safe_malloc(size_t size, int nb)
{
    void *ptr;
    if (size == 0)
        return (NULL);
    ptr = calloc(size, nb);
    if (!ptr)
    {
        perror(RED"Malloc failed"RST);
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

void *safe_realloc (void *ptr, size_t size)
{
    void *new_ptr;

    new_ptr = realloc(ptr, size);
    if (!new_ptr && size != 0)
    {
        perror(RED"Realloc failed"RST);
        exit(EXIT_FAILURE);
    }
    return (new_ptr);
}

pid_t Fork(void)
{
    pid_t pid;
    
    pid = fork();
    if (pid < 0)
    {
        perror(RED"Fork failed"RST);
        exit(EXIT_FAILURE);
    }
    return (pid);
}

void Execvp(const char *file, char *const argv[])
{
    if (!file || !*file || !argv || !*argv) 
    {
        fprintf(stderr, RED"Execvp : invalid or empty command\n"RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(file, argv) == -1)
    {
        perror(RED"SHELL_J failed"RST);
        exit(EXIT_FAILURE);
    }
}
