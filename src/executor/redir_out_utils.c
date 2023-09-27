/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:21:00 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/27 11:23:50 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_hdoc(t_tree **root, t_cmd *cmd) // 2 breve explicacao
{
	t_tree	*tmp;

	cmd->pos = 0;
	tmp = *root;
	while (tmp)
	{
		if (cmd->pos != 1 && tmp->right)
		{
			cmd->in = get_redir_num(tmp, cmd->pos, E_IN);
			if (handle_hdoc(&tmp, cmd))
				return (true);
		}
		if (cmd->pos)
			tmp = tmp->parent;
		cmd->pos++;
	}
	return (false);
}

static int	redir_write_out(t_tree *node, int fd) //2 ok
{
	if (node->type == E_STDOUT)
		fd = open(node->content, O_CREAT | O_RDONLY | O_TRUNC, S_STDPERMS);
	else if (node->type == E_APPEND)
		fd = open(node->content, O_CREAT | O_RDONLY | O_APPEND, S_STDPERMS);
	if (fd < 0)
		print_shell_err("failed to create file", node->content, EXIT_FAILURE);
	return (fd);
}

void	redir_out(t_tree *node, t_cmd *cmd, int out_num) //2 ok
{
	int	p;
	int	fd;

	p = 0;
	while (node)
	{
		if (node->type == E_STDOUT || node->type == E_APPEND)
		{
			fd = redir_write_out(node, fd);
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
