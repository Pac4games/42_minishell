/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:30:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/23 16:38:58 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_cur_env(char **env)
{
	int		p;
	char	**res;

	p = 0;
	while (env[p++])
		continue ;
	res = malloc(sizeof(char *) * (p + 1));
	if (!res)
		print_err("failed to allocate memory", EXIT_FAILURE);
	p = 0;
	while (env[p])
	{
		if (!ft_strncmp(env[p], "SHLVL=", 6))
			res[p] = shlvl_up(env[p]);
		else
			res[p] = ft_strdup(env[p]);
		p++;
	}
	res[p] = NULL;
	return (res);
}
