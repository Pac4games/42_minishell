/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:43:08 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/09 15:49:51 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **env, int fd)
{
	int	i;

	i = -1;
	while (env[++i])
		if (find_eq_sign(env[i]) != -1)
			ft_putendl_fd(env[i], fd);
	return (1);
}
