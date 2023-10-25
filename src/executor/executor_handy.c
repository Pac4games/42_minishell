/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:32:02 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/25 15:40:25 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	holy_pid_initializer(int *cmdpid, int *proc_stts)
{
	*cmdpid = 0;
	*proc_stts = 0;
}

void	pc_utils(t_cmd *cmd, t_tree *node, char *path, char **cmds)
{
	if (builtin_ret(node, cmd->env, get_cmd(node, cmd->pos), cmd->pos))
	{
		fd_close_all(0);
		free_tree(get_tree_root(&node));
		exit(*exit_stts());
	}
	if (!*cmds)
		cmds = ft_split(" ", 0);
	if (!path)
	{
		path = *cmds;
		print_shell_err(path, "command not found", 127);
	}
}

void	check_cmd(t_cmd *cmd, t_tree *node)
{
	char	*path;

	path = get_cmd_path(get_cmd(node, cmd->pos), *(cmd->env));
	if (!path)
		print_shell_err(node->content, "command not found", 127);
	else
		free(path);
}
