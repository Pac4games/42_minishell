/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:50:37 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/21 12:51:14 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_mtx(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		ft_putendl_fd(mtx[p++], STDOUT_FILENO);
}

void	print_err(char *msg, int stts)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_stts = stts;
	exit(g_stts);
}

void	print_shell_err(char *cmd, char *msg, int stts)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	free(cmd);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_stts = stts;
	exit(g_stts);
}
