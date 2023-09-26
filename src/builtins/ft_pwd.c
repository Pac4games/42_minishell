/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:09 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/25 21:52:41 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int fd) //ok
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_shell_err("pwd", "couldn't get working directory", NO_EXIT);
		return (1);
	}
	ft_putendl_fd(pwd, fd);
	free(pwd);
	return (1);
}
