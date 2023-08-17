/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:35:46 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/17 13:47:45 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mtx(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		free(mtx[p++]);
	free(mtx);
}

void	free_tree(t_tree **node)
{
	if (!node || !(*node))
		return ; 
	free_tree(&((*node)->left));
	free_tree(&((*node)->right));
	if ((*node)->input)
		free((*node)->input);
	free(*node);
	*node = NULL;
}

t_tree	**get_tree_root(t_tree **node)
{
	t_tree *root;

	if (!(*node))
		return (NULL);
	root = *node;
	while (root->parent)
		root = root->parent;
	*node = root;
	return (node);
}
