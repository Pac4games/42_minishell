/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:19:06 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/09 11:21:56 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_tree *node, char **env, char *cmd, int pos)
{
	int	fd;

	fd = 1;
	if (cmd && ft_strncmp(cmd, "exit", ft_strlen("exit") + 1))
}
