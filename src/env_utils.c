/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:30:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/10 12:44:13 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cur_env(t_list **env, char **envp)
{
	int	p;

	p = 0;
	while (envp[p])
		ft_lstadd_back(env, ft_lstnew(ft_strdup(envp[p++])));
}
