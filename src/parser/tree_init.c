/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:55:14 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/11 14:36:47 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	tree_add_branch(t_tree **node, char *arg, t_ndtype type, bool isleft)
{
	t_tree	*branch;

	branch = malloc(sizeof(*branch));
	branch->type = type;
	branch->content = arg;
	branch->left = NULL;
	branch->right = NULL;
	branch->parent = *node;
	if (!(*node))
	{
		*node = branch;
		branch = branch->parent;
	}
	else if (isleft)
		(*node)->left = branch;
	else
		(*node)->right = branch;
}

void	tree_add_n_parse(t_tree **node, char *arg, t_ndtype type)
{
	t_tree	*tmp;

	if (!(*node))
		tree_add_branch(node, arg, type, true);
	else
	{
		tmp = *node;
		while (tmp->left)
			tmp = tmp->left;
		tree_add_branch(&tmp, arg, type, true);
	}
}

void	tree_add_node(char *arg, t_ndtype type, t_parse parse)
{
	t_tree	*node;

	node = *(parse.tree);
	while (parse.pos - 1 > 0)
	{
		node = node->parent;
		parse.pos--;
	}
	if (parse.pos == 0)
		while (node->left)
			node = node->left;
	else
		while (node->right)
			node = node->right;
	if (parse.pos == 0)
		tree_add_branch(&node, arg, type, true);
	else
		tree_add_branch(&node, arg, type, false);
}
