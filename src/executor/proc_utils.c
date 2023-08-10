/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:44:43 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/10 15:28:23 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	proc_exec(t_tree **root, t_list **env, int cmd_num)
{
	t_tree	*tmp;
	t_cmd	cmd;

	cmd.num = cmd_num;
	cmd.env = *env;
	cmd.fd = 0;
	tmp = *root;
}

void	proc_run_cmd(t_tree *node, t_list *env, t_cmd *cmd)
{
	if (pipe(node->fd) == -1)
		ft_putendl_fd("Error: failed to create pipe.", STDERR_FILENO);
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_putendl_fd("Error: failed to create fork.", STDERR_FILENO);
}

void	proc_run_fr(t_tree *node, t_list *env, t_cmd *cmd)
{
	char	**env_mtx;
	char	*path;

	env_mtx = lst2mtx(env);
}
