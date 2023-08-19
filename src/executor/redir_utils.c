/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:02:27 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/19 17:09:33 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_redir_num(t_tree *node, t_cmd *cmd, int *fd)
{
	int	res;

	res = 0;
	while (node)
	{
		if ((node->type == E_GREATER || node->type == E_GGREATER))
			res++;
	}
}

void	redir(t_tree *node, t_cmd *cmd, int *fd)
{
	
}
