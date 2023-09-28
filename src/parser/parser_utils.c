/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:35:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/28 11:59:41 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_part1(char *arg, int *i) // 2 novamente "'
{
	if (*syntax())
		return ;
	if (!is_diff_sign("\"'", arg[*i]))
		*i = quotes_skip(arg, *i);
	//printf("saiu de parse_part1 com i %d\n", *i);
}

void	parse_all(t_tree **root, char *arg, t_pipe **pipes, int num) //2 ok
{
	printf("entrou em parse_all\n");
	int	i;

	i = 0;
	while (arg[i])
	{
		parse_part1(arg, &i);
		if (*syntax())
			return (free(arg));
		if (arg[i] == '|' && arg[i + 1] && arg[i + 1] != '|')
		{
			printf("olha o pipe de novo\n");
			tree_add_pipe(root);
			pipe_add2pos(pipes, i, num);
			num++;
		}
		if (arg[i])
			i++;
		if (*syntax())
			return (free(arg));
	}
}
