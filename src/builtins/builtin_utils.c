/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:19:06 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/09 21:32:35 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_tree *node, char ***env, char *cmd, int pos)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (cmd && !ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "exit", 5))
		return (ft_exit(get_cmd_args(node, pos)));
	if (cmd && !ft_strncmp(cmd, "echo", 5))
		return (ft_echo(get_cmd_args(node, pos), fd));
	if (cmd && !ft_strncmp(cmd, "env", 4))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "export", 7))
		return (ft_export(get_cmd_args(node, pos), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", 6))
		return (ft_unset(get_cmd_args(node, pos), env));
	if (cmd && !ft_strncmp(cmd, "cd", 3))
		return (ft_cd(get_cmd_args(node, pos), env));
	return (false);
}
