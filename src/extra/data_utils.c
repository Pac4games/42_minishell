/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:29:07 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/07 17:43:46 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*data(void)
{
	static t_data	*data;

	return (data);
}

void	free_cmd_data(void)
{
	int	p;

	p = 0;
	free(data()->str_cmd);
	free_mtx(data()->env_p);
	while (data()->cmds[p])
		free_mtx(data()->cmds[p++]);
	free(data()->cmds);
}
