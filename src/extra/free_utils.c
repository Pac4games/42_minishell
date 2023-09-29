/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:35:46 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/29 15:50:17 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mtx(char **mtx) // 2ok
{
	printf("entrou free_mtx\n");
	int	p;

	p = 0;
	if (!mtx) //DEFENSIVA ADD
		return ;
	while (mtx[p])
		free(mtx[p++]);
	free(mtx);
}

void	free_tree(t_tree **node)// 2 ok
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

t_tree	**get_tree_root(t_tree **node) //2 ok
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

int	mtx_len(char **mtx) // 2ok
{
	int	res;

	res = 0;
	while (mtx[res++])
		continue ;
	return (res);
}
