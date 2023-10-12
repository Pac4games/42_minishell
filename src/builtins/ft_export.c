/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:41:20 by jferreir          #+#    #+#             */
/*   Updated: 2023/10/12 14:18:38 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	no_args(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(env[i++], fd);
	}
	return (1);
}

static void	export_arg(char *arg, char ***env)
{
	int	i;

	i = -1;
	while ((*env)[++i])
	{
		if ((find_eq_sign((*env)[i]) == -1 && \
			!ft_strncmp((*env)[i], arg, ft_strlen((*env)[i]))))
			return (export_arg_new(arg, env, i));
		else if (!ft_strncmp((*env)[i], arg, find_eq_sign((*env)[i])))
		{
			if (!arg[find_eq_sign((*env)[i])])
			{
				free(arg);
				return ;
			}
			else if (arg[find_eq_sign((*env[i]))] == '=')
				break ;
		}
	}
	export_arg_new(arg, env, i);
}

int	ft_export(char **args, char ***env, int fd)
{
	int	i;

	if (mtx_len(args) == 1)
	{
		free_mtx(args);
		return (no_args(*env, fd));
	}
	else if (ft_isdigit(args[1][0]))
	{
		ft_putstr_fd("MiniHell: export: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
		free_mtx(args);
		return (0);
	}
	i = 0;
	while (args[i])
		export_arg(ft_strdup(args[i++]), env);
	free_mtx(args);
	return (1);
}
