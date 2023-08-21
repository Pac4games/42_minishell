/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:02:27 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/21 12:55:02 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_redir_num(t_tree *node, int pos, t_io io)
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

static void	redir_stdin(t_tree *node, t_cmd *cmd, int p, int in_num)
{
	int	fd;

	fd = open(node->content, O_RDONLY, S_STDPERMS);
	if (fd < 0)
		print_shell_err("failed to open file", node->content, EXIT_FAILURE);
	if (p != in_num)
		close(fd);
	else
		dup2(fd, STDIN_FILENO);
}

static void	redir_in(t_tree *node, t_cmd *cmd)
{
	int	p;

	p = 0;
	cmd->heredoc = 0;
	while (node)
	{

	}
}

void	redir(t_tree *node, t_cmd *cmd, int *fd)
{
	int	in_num;
	int	out_num;

	in_num = get_redir_num(node, cmd->pos, E_IN);
	out_num = get_redir_num(node, cmd->pos, E_OUT);
	if (!in_num)
	{
		if (*fd)
			close(*fd);
	}
}
