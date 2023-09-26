/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:35:46 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/26 11:36:57 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mtx(char **mtx) //ok
{
	int	p;

	p = 0;
	while (mtx[p])
		free(mtx[p++]);
	free(mtx);
}

void	free_tree(t_tree **node)// ok
{
	if (!node || !(*node))
		return ;
	free_tree(&((*node)->left));
	free_tree(&((*node)->right));
	if ((*node)->content)
		free((*node)->content);
	free(*node);
	*node = NULL;
}

t_tree	**get_tree_root(t_tree **node) //ok
{
	t_tree	*root;

	if (!(*node))
		return (NULL);
	root = *node;
	while (root->parent)
		root = root->parent;
	*node = root;
	return (node);
}

int	mtx_len(char **mtx) //ok
{
	int	res;

	res = 0;
	while (mtx[res++])
		continue ;
	return (res);
}
