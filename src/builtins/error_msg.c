/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:35:28 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/07 17:42:09 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *option, char *var_option, char *msg, int err)
{
	errno = err;
	data()->error = err;
	ft_putstr_fd("Minishell: ", 2);
	if (option != NULL)
		ft_putstr_fd(option, 2);
	if (var_option != NULL)
		ft_putstr_fd(var_option, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	check_permission(void)
{
	if (!(access(data()->cmds[data()->curr_cmd][0], R_OK) == 0) \
	&& errno == EACCES)
	{
		error_msg(NULL, data()->cmds[data()->curr_cmd][0], \
		": Permission denied", 1);
		free_all();
		exit(126);
	}
	else
		error_msg(NULL, data()->cmds[data()->curr_cmd][0], \
		": No such file or directory", 127);
	free_all();
	exit(127);
}

void	error_exec(void)
{
	int		i;

	i = 0;
	while (data()->cmds[data()->curr_cmd][0][i] != '\0')
	{
		if (data()->cmds[data()->curr_cmd][0][i] == '/')
		{
			if (chdir(data()->cmds[data()->curr_cmd][0]) < 0)
				check_permission();
			else
			{
				error_msg(NULL, data()->cmds[data()->curr_cmd][0], \
				": Is a directory", 126);
				free_all();
				exit(126);
			}
		}
		i++;
	}
	error_msg(NULL, data()->cmds[data()->curr_cmd][0], \
	": command not found", 127);
	free_all();
	exit(127);
}

void	exit_child(void)
{
	free_all();
	swap_fd();
	swap_fd();
	exit(1);
}
