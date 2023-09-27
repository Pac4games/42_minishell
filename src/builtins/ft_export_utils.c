/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:29:48 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/27 10:59:47 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	export_fail(char *arg)//2 ok
{
	char	*msg;

	msg = ft_strjoin(arg, ": not a valid identifier");
	print_shell_err("export", msg, NO_EXIT);
	free(msg);
	return (false);
}

static bool	is_exportable(char *arg)//2 ok
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

static void	export_add(char *arg, char ***env, int size)// 2 breve explicacao
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

void	export_arg_new(char *arg, char ***env, int i)//2 ok
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
