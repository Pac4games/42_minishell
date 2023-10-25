/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:40:24 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/23 20:19:37 by psoares-         ###   ########.fr       */
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

	i = 0;
	while ((*env)[i])
	{
		if ((find_eq_sign((*env)[i]) == -1 && \
		!ft_strncmp((*env)[i], arg, ft_strlen((*env)[i]))))
			break ;
		else if (!ft_strncmp((*env)[i], arg, find_eq_sign((*env)[i])))
		{
			if (!arg[find_eq_sign((*env)[i])])
			{
				free(arg);
				return ;
			}
			if (arg[find_eq_sign((*env)[i])] == '=')
				break ;
		}
		i++;
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
		if (ft_isdigit(args[i][0]) || !ft_str_islanum(args[i]))
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
	i = 1;
	if (check_var_names(args))
		return (1);
	while (args[i])
		export_arg(ft_strdup(args[i++]), env);
	free_mtx(args);
	return (1);
}
