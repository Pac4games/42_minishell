/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:38:35 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/27 10:31:12 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_valid_input(char **args, char **env)//ok
{
	int	i;

	if (mtx_len(args) > 2)
	{
		print_shell_err("cd", "too many arguments", NO_EXIT);
		return (false);
	}
	i = 0;
	while (env && env[i])
		if (!ft_strncmp(env[i++], "HOME=", 5))
			return (true);
	print_shell_err("cd", "HOME not set", NO_EXIT);
	return (false);
}

static int	print_cd_error(char **args) //ok
{
	char	*tmp;

	tmp = NULL;
	if (mtx_len(args) > 1)
	{
		tmp = ft_strjoin(args[1], ": No such file or directory");
		print_shell_err("cd", tmp, NO_EXIT);
		free(tmp);
	}
	free_mtx(args);
	return (1);
}

static bool	set_oldpwd(char ***env, char *path)//ok owlpwd
{
	int	i;

	i = -1;
	while ((*env)[++i])
	{
		if (!strncmp((*env)[i], "OLDPWD=", 7))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("OLDPWD=", path);
			return (true);
		}
	}
	return (false);
}

int	ft_cd(char **args, char ***env)//ok para cd
{
	char	path[1025];
	char	*tmp;

	if (!(is_valid_input(&args[1], *env) || getcwd(path, 1025))) // pq 1025?
	{
		free_mtx(args);
		return (1);
	}
	if (mtx_len(args) == 1)
	{
		tmp = parse_signs(ft_strdup("$HOME"), *env);
		chdir(tmp);
		free(tmp);
	}
	else if (chdir(args[1]) == -1)
		return (print_cd_error(args));
	if (!set_oldpwd(env, path) || !getcwd(path, 1025))
	{
		free_mtx(args);
		return (1);
	}
	free_mtx(args);
	return (set_oldpwd(env, path));
}
