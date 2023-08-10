/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:50:37 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/10 12:23:45 by paugonca         ###   ########.fr       */
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
	{
		ft_putstr_fd(mtx[p++], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
