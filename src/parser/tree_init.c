/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:55:14 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/29 13:48:30 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	tree_add_branch(t_tree **node, char *arg, t_ndtype type, bool left) // 2 uma breve explicacao sera necessaria rs
{
	printf("entrou tree_add_branch\n");
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
	else if (left)
		(*node)->left = branch;
	else
		(*node)->right = branch;
}

void	tree_add_n_parse(t_tree **node, char *arg, t_ndtype type) // 2uma breve explicacao
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

void	tree_add_node(char *arg, t_ndtype type, t_parse parse) // 2 breve explicacao
{
	printf("entrou em tree_add_node com parse %p\n", parse.tree);
	t_tree	*node;

	node = *(parse.tree);
	printf("\n\nnode eh %p\n\n", node);
	while (parse.pos - 1 > 0)
	{
		printf("primeiro loop\n");
		printf("node era %p\n", node);
		node = node->parent;
		printf("node assume %p\n", node);
		parse.pos--;
	}
	printf("saiu do loop\n");
	if (parse.pos == 0)
	{
		printf("parse.pos == 0\n");
		printf("node eh %p\n", node);
		while (node->left) // se node eh nil, esse while nao execulta. aqui esta nosso seg fault!!
		{
			printf("ta no loop\n");
			printf("%p\n", node->left);
			node = node->left;
		}
		printf("tchau loop again\n");
	}
	else
	{
		printf("para else node eh %p\n", node);
		while (node->right)
			node = node->right;
	}
	if (parse.pos == 0)
	{
		printf("parse.pos eh %d\n", parse.pos);
		tree_add_branch(&node, arg, type, true);
	}
	else
	{
		printf("parse.pos eh %d\n", parse.pos);
		tree_add_branch(&node, arg, type, false);
	}
	printf("saiu de tree_add_node\n\n");
}
