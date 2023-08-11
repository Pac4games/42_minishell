/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:50:37 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/10 19:13:13 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		free(mtx[p++]);
	free(mtx);
}

void	print_matrix(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		ft_putendl_fd(mtx[p++], STDOUT_FILENO);
}

char **lst2mtx(t_list *env)
{
	int		p;
	t_list	*tmp;
	char	**mtx;

	p = 0;
	tmp = env;
	mtx = malloc(sizeof(char *) + (ft_lstsize(env)) + 1);
	while (tmp)
	{
		mtx[p++] = tmp->content;
		tmp = tmp->next;
	}
	mtx[p++] = NULL;
	return (mtx);
}
