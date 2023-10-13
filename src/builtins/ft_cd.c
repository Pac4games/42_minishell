/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:38:35 by jferreir          #+#    #+#             */
/*   Updated: 2023/10/13 11:44:29 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_cd_error(char **args)
{
	char	*msg;

	msg = ft_strjoin(SHELL, ": cd: `");
	if (access(args[1], X_OK == -1))
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		free_mtx(args);
		return (1);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd("': Not a directory\n", STDERR_FILENO);
	free(msg);
	free_mtx(args);
	return (1);
}

static int	is_valid_input(char **args, char **env)
{
	int	i;

	if (mtx_len(args) > 2)
	{
		printf("MiniHell: cd: too many arguments\n");
		return (1);
	}
	i = 0;
	while (env && env[i] != 0)
	{
		if (ft_strncmp(env[i], "HOME=", 5))
		{
			return (0);
		}
		i++;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (1);
}

int	set_oldpwd(char ***env, char *path)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (!ft_strncmp((*env)[i], "OLDPWD=", 7))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("OLDPWD=", path);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	set_updpwd(char ***env, char *path)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (!ft_strncmp((*env)[i], "PWD=", 4))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("PWD=", path);
			return (1);
		}
		i++;
	}
	return (1);
}

int	ft_cd(char **args, char ***env)
{
	char	path[1025];

	if (mtx_len(args) > 2)
	{
		printf("MiniHell: cd: too many arguments\n");
		free_mtx(args);
		return (1);
	}
	if ((is_valid_input(&args[1], *env) == 1 || getcwd(path, 1025) == NULL))
	{
		free_mtx(args);
		return (1);
	}
	if (ft_cd_weird_args(args, env))
		return (1);
	if (chdir(args[1]) == -1)
		return (print_cd_error(args));
	if (!set_oldpwd(env, path) || getcwd(path, 1025) == NULL)
	{
		free_mtx(args);
		return (1);
	}
	free_mtx(args);
	return (set_updpwd(env, path));
}
