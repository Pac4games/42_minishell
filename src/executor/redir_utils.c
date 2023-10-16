/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:18:49 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/16 15:18:50 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redir_num(t_tree *node, int pos, t_io io)
{
	int	res;

	res = 0;
	while (node)
	{
		if (((node->type == E_STDOUT || node->type == E_APPEND) && io == E_OUT)
			|| ((node->type == E_STDIN || node->type == E_HDOC) && io == E_IN))
			res++;
		if (!pos)
			node = node->left;
		else
			node = node->right;
	}
	return (res);
}

void	redir(t_tree *node, t_cmd *cmd, int *fd)
{
	int	in_num;
	int	out_num;

	in_num = get_redir_num(node, cmd->pos, E_IN);
	out_num = get_redir_num(node, cmd->pos, E_OUT);
	if (in_num)
	{
		if (*fd)
			close(*fd);
		redir_in(node, cmd, in_num);
	}
	else
		dup2(*fd, STDIN_FILENO);
	if (out_num)
	{
		close((cmd->pipes)[1]);
		redir_out(node, cmd, out_num);
	}
	else
	{
		if (cmd->pos == cmd->num - 1)
			close((cmd->pipes)[1]);
		else
			dup2((cmd->pipes)[1], STDOUT_FILENO);
	}
}
