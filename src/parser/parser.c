/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:59:05 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/10 16:40:09 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Our partner in crime and best-friend (the parser)
void	parsa(char *in, char ***env, t_tree **root, int num)
{
	int		i;
	char	**mtx;
	t_pipe	*pipes;

	i = 0;
	pipes = NULL;
	in = parse_tilde(in, *env);
	parse_pipes(in);
	if (!in)
		return ;
	
}
