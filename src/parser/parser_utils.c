/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:35:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/11 10:30:10 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_part1(char *arg, int *i)
{
	if (*syntax())
		return ;
	if (arg[*i] && !is_diff_sign("\"'", arg[*i]))
		*i = skip_quotes(arg, *i);
}

void	parse_all(t_tree **root, char *arg, t_pipe **pipes, int num)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		parse_part1(arg, &i);
		if (*syntax())
			return (free(arg));
		if (arg[i] && arg[i] == '|' && arg[i + 1] && arg[i + 1] != '|')
		{
			
		}
	}
}
