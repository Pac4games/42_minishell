/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:48:22 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/17 14:06:19 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(t_tree *node, int pos)
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

//These next 2 functions might be complicated to understand, so we will
//proceed to explain it. Because of norme limitations, we have divided this
//function in get_args() and args_set(). During phase 1, the binary tree
//is navigated while we count the number of existing nodes, this number
//being the variable "p". At the end of the "while (node)" loop, if we're
//still in phase 1, the memory for the "args" matrix will be allocated,
//and in the next function call we will set the strings for "args" as
//the input containted in the nodes with ft_strdup(). We decided to do
//this since we would need two separate identical functions to navigate
//the binary tree: one to count the number of nodes for malloc(), and
//another to duplicate the strings, so this was engineered in order to
//avoid unecessary indentical "while" loops.
static void	cmd_args_set(t_tree *node, int pos, char **args, int phase)
{
	int	p;

	while (node)
	{
		p = 0;
		if (node->type == E_ARG || node->type == E_CMD || node->type == E_FLAG)
		{
			if (phase == 1)
				p++;
			else if (phase == 2)
				args[p++] = ft_strdup(node->input);
			if (!pos)
				node = node->left;
			else
				node = node->right;
		}
	}
	if (phase == 1)
		args = malloc(sizeof(char **) * (p + 1));
	if (!args)
		print_err("failed to allocate memory", EXIT_FAILURE);
}

char	**get_cmd_args(t_tree *node, int pos)
{
	int		phase;
	t_tree	*tmp;
	char	**args;

	phase = 0;
	args = NULL;
	while (phase <= 2)
	{
		tmp = node;
		cmd_args_set(tmp, pos, args, ++phase);
	}
	return (args);
}
