/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xqt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:44:43 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/11 13:52:25 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Yes, this is the executor. Cool name, right?
void	xqt(t_tree **root, t_list **env, int cmd_num)
{
	t_tree	*tmp;
	t_cmd	cmd;

	cmd.num = cmd_num;
	cmd.env = *env;
	cmd.fd = 0;
	tmp = *root;
}

static void	run_cmd_fr(t_tree *node, t_list *env, t_cmd *cmd)
{
	char	**env_mtx;
	char	*path;

	env_mtx = lst2mtx(env);
	path = get_cmd_path(((char **)node->token)[0], env, env_mtx);
	close(node->fds[0]);
	if (path)
		execve(path, node->token, env_mtx);
	free_mtx(env_mtx);
	close(node->fds[1]);
	close(node->fds[0]);
	close(cmd->fd);
}

static void	run_cmd(t_tree *node, t_list *env, t_cmd *cmd)
{
	if (pipe(node->fds) == -1)
		ft_putendl_fd("Error: failed to create pipe.", STDERR_FILENO);
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_putendl_fd("Error: failed to create fork.", STDERR_FILENO);
}
