/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:30:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/14 15:43:43 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_cur_env(char **env)
{
	char	**path;
	char	*tmp;
	int		p;

	p = 0;
	while (env[p])
	{
		if (!ft_strncmp(env[p], "PATH=", 5))
		{
			path = ft_split(env[p] + 5, ':');
			p = 0;
			while (path[p])
			{
				tmp = ft_strdup(path[p]);
				free(path[p]);
				path[p] = ft_strjoin(tmp, "/");
				free(tmp);
				p++;
			}
			return (path);
		}
		p++;
	}
	return (NULL);
}
