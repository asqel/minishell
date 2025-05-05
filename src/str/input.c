/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:13:03 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/05 20:20:56 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*msh_get_input(t_msh_ctx *ctx)
{
	char	*input;
	char	*prompt;

	prompt = msh_get_prompt(ctx);
	if (prompt == NULL)
	{
		msh_free_ctx(ctx);
		print_error_exit("malloc", 1);
	}
	input = readline(prompt);
	free(prompt);
	return (input);
}
