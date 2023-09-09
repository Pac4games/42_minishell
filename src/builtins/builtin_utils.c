/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:19:06 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/09 13:16:21 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_tree *node, char ***env, char *cmd, int pos)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (cmd && !ft_strncmp(cmd, "exit", 5))
		return (ft_exit(get_cmd_args(node, pos)));
	if (cmd && !ft_strncmp(cmd, "env", 4))
		return (ft_env(*env, fd));
}
