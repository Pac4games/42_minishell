/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:48:22 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/04 11:21:52 by paugonca         ###   ########.fr       */
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
		return (node->content);
	return (NULL);
}

static int	get_cmd_arg_num(t_tree *node, int pos)
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

char	**get_cmd_args(t_tree *node, int pos)
{
	int		p;
	char	**args;

	p = 0;
	args = malloc((get_cmd_arg_num(node, pos + 1)) * sizeof(char *));
	if (!args)
		print_err("failed to allocate memory", EXIT_FAILURE);
	while (node)
	{
		if (node->type == E_ARG || node->type == E_FLAG || node->type == E_CMD)
			args[p++] = ft_strdup(node->content);
		if (!pos)
			node = node->left;
		else
			node = node->right;
	}
	args[p] = NULL;
	return (args);
}

int	get_cmd_num(t_tree *node)
{
	int	res;

	res = 0;
	while (node)
	{
		if (!res && node->right)
			res++;
		res++;
		node = node->parent;
	}
	printf("res %d\n", res);
	return (res);
}
