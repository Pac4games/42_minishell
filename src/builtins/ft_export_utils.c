/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:40:30 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/19 16:29:10 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_fail(char *arg)
{
	ft_putstr_fd(SHELL ": export:  `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (0);
}

static int	is_exportable(char *arg)
{
	int	i;

	if (!(ft_strlen(arg)))
	{
		*exit_stts() = 1;
		return (export_fail(arg));
	}
	if (!((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')))
	{
		*exit_stts() = 1;
		return (export_fail(arg));
	}
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!is_var(arg[i]))
		{
			*exit_stts() = 1;
			return (export_fail(arg));
		}
		i++;
	}
	return (1);
}

static void	export_add(char *arg, char ***env, int size)
{
	int		i;
	char	**new_env;

	if (!is_exportable(arg))
		return ;
	i = -1;
	new_env = malloc(sizeof(char *) * (size + 2));
	while (++i < size)
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	free_mtx(*env);
	*env = new_env;
}

void	export_arg_new(char *arg, char ***env, int i)
{
	if (!((*env)[i]))
		export_add(arg, env, i);
	else
	{
		free((*env)[i]);
		(*env)[i] = ft_strdup(arg);
	}
	free(arg);
}
