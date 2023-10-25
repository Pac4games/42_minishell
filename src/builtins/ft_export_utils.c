/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:40:30 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/23 10:38:44 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_fail(char *arg)
{
	char	*msg;

	msg = ft_strjoin(SHELL, ": export: `");
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	*exit_stts() = 1;
	free(msg);
	return (1);
}

static bool	is_exportable(char *arg)
{
	int	i;

	if (!(ft_strlen(arg) || ft_isalpha(arg[0])))
		return (export_fail(arg));
	i = 0;
	while (arg[i] && arg[i] != '=')
		if (!is_var(arg[i++]))
			return (export_fail(arg));
	return (true);
}

static void	export_add(char *arg, char ***env, int size)
{
	int		i;
	char	**new_env;

	if (!is_exportable(arg))
		return ;
	i = -1;
	new_env = malloc((size + 2) * sizeof(char *));
	while (++i < size)
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i] = ft_strdup(arg);
	new_env[++i] = NULL;
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

int	ft_str_islanum(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}