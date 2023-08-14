/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xqt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:51:17 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/14 15:25:23 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//The actual executor function. Cool name, right?
void	xqt(t_tree **root, t_cmd *cmd, int *fd)
{
	if (pipe(cmd->pipes) == -1)
		print_err("failed to open pipe.", EXIT_FAILURE);
	cmd->pid = fork();
	if (cmd->pid < 0)
		print_err("failed to fork process.", EXIT_FAILURE);
}
