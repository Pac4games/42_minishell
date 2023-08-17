/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:51:17 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/17 14:14:04 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	proc_child(t_tree *node, t_cmd *cmd)
{
	close((cmd->pipes)[0]);
	execve(get_cmd_path(get_cmd(node, cmd->pos), *(cmd->env)),
		get_cmd_args(node, cmd->pos), *(cmd->env));
	free_tree(get_tree_root(&node));
	g_stts = 127;
	exit(127);
}

//The actual executor function. Cool name, right?
void	xqt(t_tree *root, t_cmd *cmd, int *fd)
{
	if (pipe(cmd->pipes) == -1)
		print_err("failed to open pipe.", EXIT_FAILURE);
	cmd->pid = fork();
	if (cmd->pid < 0)
		print_err("failed to fork process.", EXIT_FAILURE);
	else if (cmd->pid == 0)
		proc_child(root, cmd);
	if (cmd->num != 1)
	{
		if ((*fd) < 0)
			close(*fd);
		close((cmd->pipes[1]));
		*fd = cmd->pipes[0];
	}
}
