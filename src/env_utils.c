/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:30:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/26 07:54:15 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//ok
char	**get_cur_env(char **env)//ok
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
