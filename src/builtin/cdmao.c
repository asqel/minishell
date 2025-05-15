/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdmao.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:41:23 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/12 18:41:26 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int	cd_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		fprintf(stderr, "cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	cd_to_previous(void)
{
	char	*old_pwd;

	old_pwd = getenv("OLDPWD");
	if (!old_pwd)
	{
		fprintf(stderr, "cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(old_pwd) == -1)
	{
		perror("cd");
		return (1);
	}
	printf("%s\n", old_pwd);
	return (0);
}

static int	cd_to_directory(char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static void	update_pwd_env(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		perror("cd");
		return;
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", current_dir, 1);
	free(current_dir);
}

int	cd_builtin(char **args)
{
	int	ret;

	ret = 0;
	if (args[1] == NULL)
		ret = cd_to_home();
	else if (strcmp(args[1], "-") == 0)
		ret = cd_to_previous();
	else
		ret = cd_to_directory(args[1]);
	if (ret == 0)
		update_pwd_env();
	return (ret);
}
