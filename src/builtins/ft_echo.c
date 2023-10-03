/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:12:11 by jferreir          #+#    #+#             */
/*   Updated: 2023/10/03 12:13:49 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_flag(char *arg)//2 ok
{
	int	i;

	i = -1;
	while (arg[++i])
		if ((!i && arg[i] != '-') || (i && arg[i] != 'n'))
			return (false);
	return (true);
}

int	ft_echo(char **args, int fd) // 2 ok para echo
{
	int	i;

	i = 1;
	if (mtx_len(args) > 1 && is_flag(args[1]))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[++i])
			ft_putstr_fd(" ", fd);
	}
	if (!(mtx_len(args) > 1 && is_flag(args[1])))
		ft_putchar_fd('\n', fd);
	free_mtx(args);
	g_stts = EXIT_SUCCESS;
	return (1);
}
