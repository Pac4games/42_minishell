/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:44:19 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/10 16:44:29 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_pipes_utils(char *arg, int *i)
{
	while (arg[*i])
	{
		if (arg[*i] && !is_diff_sign("\"'", arg[*i]))
			*i = skip_quotes(arg, *i);
		if (arg[*i] && !is_diff_sign("|", arg[*i]))
		{
			(*i)++;
			while (arg[*i] && (arg[*i] == ' ' || arg[*i == '\t']))
				(*i)++;
			if (arg[*i] && !is_diff_sign("|", arg[*i]))
				print_syntax_error();
		}
		else
			(*i)++;
		if (*syntax())
			return ;
	}
}

void	parse_pipes(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	if (arg[i] && !is_diff_sign("|", arg[i]))
		print_syntax_error();
	parse_pipes_utils(arg, &i);
	if (*syntax())
		return ;
}
