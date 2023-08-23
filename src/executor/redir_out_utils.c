/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:21:00 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/22 12:49:22 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		redir_heredoc(t_tree **root, t_cmd *cmd)
{
	t_tree	*tmp;

	cmd->pos = 0;
	tmp = *root;
	while (tmp)
	{
		if (cmd->pos != 1 && tmp->right)
		{
			cmd->in = get_redir_num(tmp, cmd->pos, E_IN);
		}
	}
}

void	redir_out(t_tree *node, t_cmd *cmd, int out_num)
{
	int	p;
	int	fd;

	p = 0;
	while (node)
	{
		if (node->type == E_STDOUT || node->type == E_APPEND)
		{
			if (node->type == E_STDOUT)
				fd = open(node->content, O_STDOUTFILE, S_STDPERMS);
			else
				fd = open(node->content, O_STDAPPEND, S_STDPERMS);	
			if (fd < 0)
				print_shell_err("failed to create file", node->content, 1);
			p++;
			if (p != out_num)
				close(fd);
			else
				dup2(fd, STDOUT_FILENO);
		}
		if (!(cmd->pos))
			node = node->left;
		else
			node = node->right;
	}
}
