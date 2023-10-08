/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:43:43 by jferreir          #+#    #+#             */
/*   Updated: 2023/10/08 16:37:20 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
static bool	is_num(char *str)
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
}*/

static int	is_nbr(char *str)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (!nbr)
			nbr = 1;
		i++;
	}
	if (!str[i] && nbr)
		return (1);
	return (0);
}

static int	quit(char **args, int isnum)
{
	if (isnum == 1 && args[2])
	{
		ft_putstr_fd(SHELL, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
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
	exit(2);
	return (-42);
}

/*int	ft_exit(char **args)
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
}*/

int	ft_exit(char **args)
{
	int	nbr;

	nbr = 0;
	if ((args[1] && is_nbr(args[1])) || args[0])
		nbr = 1;
	if ((nbr == 1 && mtx_len(args) == 2) || mtx_len(args) == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if (nbr == 1)
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
	return (quit(args, nbr));
}
