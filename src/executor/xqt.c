/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xqt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:51:17 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/16 12:48:03 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

static char	*get_cmd(t_tree *node, int pos)
{
	if (!pos)
		while (node && node->type != E_CMD)
			node = node->left;
	else
		while (node && node->type != E_CMD)
			node = node->right;
	if (node)
		return (node->input);
	return (NULL);
}

static int	get_arg_num(t_tree *node, int pos)
{
	int	res;

	res = 0;
	while (node)
	{
		if (node->type == E_ARG || node->type == E_FLAG || node->type == E_CMD)
			res++;
		if (!pos)
			node = node->left;
		else
			node = node->right;
	}
	return (res);
}

static char	**get_args(t_tree *node, int pos)
{
	int		p;
	char	**args;

	p = 0;
	args = malloc(sizeof(char *) * (get_arg_num(node, pos) + 1));
	if (!args)
		print_err("memory allocation failed", STDERR_FILENO);
}

static void	proc_child(t_tree *node, t_cmd *cmd, int *fd)
{
	close((cmd->pipes)[0]);
}

//The actual executor function. Cool name, right?
void	xqt(t_tree **root, t_cmd *cmd, int *fd)
{
	if (pipe(cmd->pipes) == -1)
		print_err("failed to open pipe.", EXIT_FAILURE);
	cmd->pid = fork();
	if (cmd->pid < 0)
		print_err("failed to fork process.", EXIT_FAILURE);
}
