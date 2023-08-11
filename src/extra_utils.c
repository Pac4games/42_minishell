/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:50:37 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/11 10:42:28 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mtx(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		free(mtx[p++]);
	free(mtx);
}

void	print_mtx(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		ft_putendl_fd(mtx[p++], STDOUT_FILENO);
}

char **lst2mtx(t_list *lst)
{
	int		p;
	t_list	*tmp;
	char	**mtx;

	p = 0;
	tmp = lst;
	mtx = malloc(sizeof(char *) + (ft_lstsize(lst)) + 1);
	while (tmp)
	{
		mtx[p++] = tmp->content;
		tmp = tmp->next;
	}
	mtx[p++] = NULL;
	return (mtx);
}
