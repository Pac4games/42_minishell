/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:50:37 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/14 14:58:20 by paugonca         ###   ########.fr       */
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

void	print_stderr(char *msg, int stts)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_stts = stts;
	exit(g_stts);
}

void	print_shellerr(char *cmd, char *msg, int stts)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_stts = stts;
	exit(g_stts);
}
