/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:10:49 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/15 17:11:14 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirect_input(int in_fd)
{
    close(0);
    if (fcntl(in_fd, F_GETFD) == -1) {
        perror("Failed to duplicate file descriptor for input");
        exit(EXIT_FAILURE);
    }
    if (fcntl(in_fd, F_DUPFD, 0) == -1) {
        perror("Failed to duplicate file descriptor for input");
        exit(EXIT_FAILURE);
    }
    close(in_fd);
}

void redirect_output(int pipefds[2])
{
    close(1);
    if (fcntl(pipefds[1], F_GETFD) == -1) {
        perror("Failed to duplicate file descriptor for output");
        exit(EXIT_FAILURE);
    }
    if (fcntl(pipefds[1], F_DUPFD, 1) == -1) {
        perror("Failed to duplicate file descriptor for output");
        exit(EXIT_FAILURE);
    }
    close(pipefds[0]);
    close(pipefds[1]);
}
