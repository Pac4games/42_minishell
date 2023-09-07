/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:42:13 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/07 17:47:04 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_var(char **env, int skip)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (env && env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (env && env[i] != NULL)
	{
		if (i == skip)
			i++;
		else
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
			i++;
		}
	}
	new_env[j] = NULL;
	free_mtx(data()->env_p);
	data()->env_p = new_env;
}

void	ft_unset(char **str, char *find)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_strncmp(str[i], find, ft_strlen(find)) \
		&& str[i][ft_strlen(find)] == '=')
		{
			unset_var(str, i);
			return ;
		}
		i++;
	}
}
