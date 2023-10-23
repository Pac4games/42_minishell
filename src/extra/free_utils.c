/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:38:35 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/23 21:02:41 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mtx(char **mtx)
{
	int	p;

	p = 0;
	if (!mtx)
		return ;
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
	if ((*node)->content)
		free((*node)->content);
	free(*node);
	*node = NULL;
}

void	fodase2(t_tree **node)
{
	t_tree *a = *node;
	if (!node || !(*node))
		return ;
	fodase2(&((*node)->left));
	fodase2(&((*node)->right));

	if((*node)->type == E_BUILTIN && (*node)->pipes[1] > 2)
		close((*node)->pipes[1]);
	if((*node)->type == E_BUILTIN && (*node)->pipes[0] > 2)
		close((*node)->pipes[0]);
	if((*node)->type == E_CMD && ((t_cmd *)*node)->pipes[1] > 2)
		close(((t_cmd *)*node)->pipes[1]);
	if((*node)->type == E_CMD && ((t_cmd *)*node)->pipes[0] > 2)
		close(((t_cmd *)*node)->pipes[0]);
	*node = a;
}

void fodase3(t_tree **node){
	t_tree *a = *node;
	
		if (!node || !(*node))
		return ;
	fodase3(&((*node)->left));
	fodase3(&((*node)->right));

	if((*node)->type == E_HDOC && (*node)->pipes[1] > 2)
	close((*node)->pipes[1]);
		if((*node)->type == E_HDOC && (*node)->pipes[0] > 2)
	close((*node)->pipes[0]);
	*node =a;
}
t_tree	**get_tree_root(t_tree **node)
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

int	mtx_len(char **mtx)
{
	int	res;

	res = 0;
	while (mtx[res])
		res++;
	return (res);
}
