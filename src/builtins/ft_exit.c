/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:43:43 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/26 11:42:09 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_num(char *str) //-
{
	int		i;
	bool	check;

	i = 0;
	check = false;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (!check)
			check = true;
		i++;
	}
	if (!str[i] && check)
		return (true);
	return (false);
}

static int	quit(char **args, bool isnum) //ok
{
	if (isnum && args[2])
	{
		ft_putstr_fd(SHELL, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments", STDERR_FILENO);
		free_mtx(args);
		g_stts = EXIT_FAILURE;
		return (-1);
	}
	g_stts = 2;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(":	numeric argument required\n", STDERR_FILENO);
	free_mtx(args);
	rl_clear_history();
	exit(g_stts);
	return (-42);
}

int	ft_exit(char **args) //ok
{
	bool	isnum;

	isnum = is_num(args[1]);
	if (args[1] && isnum)
		isnum = true;
	if ((isnum && mtx_len(args) == 2) || mtx_len(args) == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if (isnum)
		{
			g_stts = (unsigned int) ft_atoi(args[1]);
			free_mtx(args);
			rl_clear_history();
			exit(g_stts);
		}
		free_mtx(args);
		rl_clear_history();
		exit(g_stts);
	}
	return (quit(args, isnum));
}
