/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:41:20 by jferreir          #+#    #+#             */
/*   Updated: 2023/10/13 11:35:45 by paugonca         ###   ########.fr       */
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

static int	check_var_names(char **args)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (args[++i])
	{
		if (ft_isdigit(args[i][0]))
			res = export_fail(args[i]);
	}
	if (res)
		free_mtx(args);
	return (res);
}

int	ft_export(char **args, char ***env, int fd)
{
	int	i;

	if (mtx_len(args) == 1)
	{
		free_mtx(args);
		return (no_args(*env, fd));
	}
	i = 0;
	if (check_var_names(args))
		return (1);
	while (args[i])
		export_arg(ft_strdup(args[i++]), env);
	free_mtx(args);
	return (1);
}
