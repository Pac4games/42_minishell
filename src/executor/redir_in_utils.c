/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:10:56 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/09 11:42:07 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redir_stdin(t_tree *node, int p, int in_num)
{
	int	fd;

	fd = open(node->content, O_RDONLY, S_STDPERMS);
	if (fd < 0)
		print_shell_err("failed to open file", node->content, EXIT_FAILURE);
	if (p != in_num)
		close(fd);
	else
		if (dup2(fd, STDIN_FILENO) < 0)
			print_shell_err("failed to duplicate file", node->content,
				EXIT_FAILURE);
}

void	redir_in(t_tree *node, t_cmd *cmd, int in_num)
{
	int	p;

	p = 0;
	cmd->heredoc = false;
	while (node)
	{
		if (node->type == E_STDIN || node->type == E_HDOC)
		{
			p++;
			if (node->type == E_STDIN)
				redir_stdin(node, p, in_num);
			else
			{
				if (p == in_num)
					dup2((node->pipes)[0], STDIN_FILENO);
				cmd->heredoc = true;
			}
		}
		if (!(cmd->pos))
			node = node->left;
		else
			node = node->right;
	}
}
