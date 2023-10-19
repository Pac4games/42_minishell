/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:51:17 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/16 14:57:01 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	proc_child(t_tree *node, t_cmd *cmd, int *fd)
{
	close((cmd->pipes[0]));
	redir(node, cmd, fd);
	//sig_handle(E_SIG_DFL);
	rl_clear_history();
	if (builtin_ret(node, cmd->env, get_cmd(node, cmd->pos), cmd->pos))
		exit(*exit_stts());
	execve(get_cmd_path(get_cmd(node, cmd->pos), *(cmd->env)),
		get_cmd_args(node, cmd->pos), *(cmd->env));
	free_tree(get_tree_root(&node));
	*exit_stts() = 127;
	exit(*exit_stts());
}

//The actual executor function. Cool name, right?
void	xqt(t_tree *node, t_cmd *cmd, int *fd)
{
	cmd->pid = fork();
	if (pipe(cmd->pipes) == -1)
	{
		print_err("failed to open pipe", EXIT_FAILURE);
		*exit_stts() = 1;
		exit (1);
	}
	if (cmd->pid < 0)
	{
		print_err("failed to fork process", EXIT_FAILURE);
		*exit_stts() = 1;
		exit (1);
	}
	else if (cmd->pid == 0)
		proc_child(node, cmd, fd);
	if (cmd->num != 1)
	{
		if ((*fd) > 0)
			close(*fd);
		close((cmd->pipes[1]));
		*fd = cmd->pipes[0];
	}
}

static t_cmd	proc_exec_cmd(t_tree *node, char ***env, int pos, int cmd_num)
{
	t_cmd		cmd;
	static int	fd;

	if (!pos)
		fd = 0;
	cmd.env = env;
	cmd.num = cmd_num;
	cmd.pos = pos;
	xqt(node, &cmd, &fd);
	return (cmd);
}

static int	pet_utils(t_tree **root, t_cmd *cmd, int *i, int *cmd_num)
{
	*i = 0;
	if (redir_hdoc(root, cmd))
		return (1);
	*cmd_num = get_cmd_num(*root);
	return (0);
}

void	proc_exec_tree(t_tree **root, char ***env)
{
	int		p;
	int		cmd_num;
	int		proc_stts;
	t_cmd	cmd;
	t_tree	*tmp;

	p = 0;
	if (pet_utils(root, &cmd, &p, &cmd_num))
		return ;
	if (cmd_num == 1 && is_builtin(*root, env, get_cmd(*root, 0)))
		return ;
	tmp = *root;
	while (tmp)
	{
		if (!(p == 1 && !(tmp->right)))
			cmd = proc_exec_cmd(tmp, env, p, cmd_num);
		if (p)
			tmp = tmp->parent;
		p++;
	}
	waitpid(cmd.pid, &proc_stts, 0);
	set_exit_stts(proc_stts);
	p = 0;
	while (p++ < cmd_num)
		wait(NULL);
}
