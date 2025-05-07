/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:27:04 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/07 19:32:46 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int msh_blt_echo(int argc, char **argv)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    if (i < argc && ft_strcmp(argv[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (i < argc)
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
		printf("\n");
	return (0);
}
