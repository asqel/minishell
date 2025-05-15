/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:20:26 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/07 21:14:14 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (argv[i] && strcmp(argv[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	cmd_cd(char **argv)
{
	if (!argv[1])
	{
		fprintf(stderr, "cd: missing argument\n");
		return ;
	}
	if (chdir(argv[1]) != 0)
		perror("cd");
}

void	cmd_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	cmd_exit(char **argv)
{
	int	exit_status;
	int	i;

	i = 0;
	exit_status = 0;
	if (argv[1])
		exit_status = atoi(argv[1]);
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	exit(exit_status);
}
