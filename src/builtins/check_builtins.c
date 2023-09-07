/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:04:45 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/07 17:04:54 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4))
		return (1);
	else if (ft_strncmp(cmd, "cd", 2))
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3))
		return (1);
	else if (ft_strncmp(cmd, "export", 6))
		return (1);
	else if (ft_strncmp(cmd, "unset", 5))
		return (1);
	else if (ft_strncmp(cmd, "env", 3))
		return (1);
	else if (ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

void	call_builtins(char **cmd)
{
	int	tmp_curr;

	tmp_curr = data()->curr_cmd + 1;
	if (data()->curr_cmd && is_spc(data()->cmds[tmp_curr][0]))
		tmp_curr = fd_check(tmp_curr);
	if (ft_strncmp(cmd[0], "echo", 4))
		ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 2))
		ft_cd(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3))
		ft_pwd(cmd);
	else if (ft_strncmp(cmd[0], "export", 6))
		ft_export();
	else if (ft_strncmp(cmd[0], "unset", 5))
		ft_unset(data()->env_p, data()->cmds[data()->curr_cmd][1]);
	else if (ft_strncmp(cmd[0], "env", 3))
		ft_env(data()->env_p);
	else if (ft_strncmp(cmd[0], "exit", 4))
		ft_exit(cmd);
	data()->curr_cmd = tmp_curr;
	swap_fd();
}

void	clean_exit_child(void)
{
	free_all();
	swap_fd();
	swap_fd();
	exit(0);
}
