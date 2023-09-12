/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:12:11 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/12 12:42:52 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_flag(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if ((!i && arg[i] != '-') || (i && arg[i] != 'n'))
			return (false);
	return (true);
}

int	ft_echo(char **args, int fd)
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
	if (mtx_len(args) <= 1 && !is_flag(args[1]))
		ft_putendl_fd(NULL, fd);
	free_mtx(args);
	g_stts = EXIT_SUCCESS;
	return (1);
}
