/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:12:11 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/06 15:02:42 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
		i++;
	else
		return (0);
	while (str && str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_echo(char **str, int flag)
{
	int	i;

	i = 1;
	if (flag == 1)
		i = 2;
	while (str[i] != NULL)
	{
		printf("%s", str[i]);
		i++;
	}
	if (flag != 1)
		printf("\n");
}

void	ft_echo_beg(char **str, int flag)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
			exit_child();
		dup2(data()->fd[0][1], STDOUT_FILENO);
		print_echo(str, flag);
		clean_exit_child();
	}
	else
	{
		waitpid(pid, &status, 0);
		data()->error = 0;
		if (status > 0)
			data()->error = status / 256;
	}
}

void	ft_echo(char **str)
{
	if (str[1] && is_flag(str[1]))
		ft_echo_beg(str, 1);
	else if (str[1] != NULL)
		ft_echo_beg(str, 0);
	else if (data()->cmds[data()->curr_cmd + 1] == NULL)
		printf("\n");
	return ;
}
