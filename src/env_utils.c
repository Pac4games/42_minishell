/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:30:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/04 11:39:30 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
/*
char	**get_cur_env(char **env)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path = ft_split(env[i] + 5, ':');
			i = 0;
			while (path[i])
			{
				tmp = ft_strdup(path[i]);
				free(path[i]);
				path[i] = ft_strjoin(tmp, "/");
				free(tmp);
				i++;
			}
			return (path);
		}
		i++;
	}
	return (NULL);
}*/