/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:31:49 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/11 12:32:15 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tree_add_pipe(t_tree **root)
{
	t_tree	*tmp;
	t_tree	*pipe;

	tmp = *root;
	pipe = malloc(sizeof(*pipe));
	pipe->type = E_PIPE;
	pipe->left = NULL;
	pipe->right = NULL;
	pipe->parent = NULL;
	pipe->content = NULL;
	if (!tmp)
	{
		*root = pipe;
		return ;
	}
	while (tmp)
		tmp = tmp->parent;
	pipe->left = tmp;
}

static void	tar_util(char *arg, int *i, int *j)
{
	while (arg[*i] == ' ' || arg[*i] == '\t')
		(*i)++;
	if (!arg[*i])
		print_syntax_error();
	*j = *i;
	while (arg[*j] == ' ' || arg[*j] == '\t')
		(*j)++;
}

int	tree_add_redir(char *arg, int i, t_ndtype type, t_parse parse)
{
	int	j;

	if (type == E_HDOC || type == E_APPEND)
		i++;
	i++;
}
