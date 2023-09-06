/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:09 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/06 15:03:07 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char **str)
{
	int		pid;
	int		status;
	char	dir[1024];

	(void) str;
	getcwd(dir, (sizeof(char) * 1024));
	pid = fork();
	if (pid == 0)
	{
		if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
			exit_child();
		dup2(data()->fd[0][1], STDOUT_FILENO);
		printf("%s\n", dir);
		clean_exit_child();
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status > 0)
			data()->error = status / 256;
		else
			data()->error = 0;
	}
}

void	ft_pwd_exec(char **str)
{
	char	dir[1024];

	(void) str;
	getcwd(dir, (sizeof(char) * 1024));
	printf("%s\n", dir);
}
