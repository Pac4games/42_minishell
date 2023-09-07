/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:38:35 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/07 17:34:52 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cd_to_env(char *path)
{
	int		j;
	char	**new_str;

	j = 0;
	while (data()->env_p && data()->env_p[j] != NULL)
		j++;
	new_str = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (data()->env_p && data()->env_p[j] != NULL)
	{
		new_str[j] = ft_strdup(data()->env_p[j]);
		j++;
	}
	new_str[j++] = ft_strdup(path);
	new_str[j] = NULL;
	free_mtx(data()->env_p);
	data()->env_p = new_str;
}

void	apply_cd(char *oldcd, char *newcd)
{
	char	*path;
	char	dir[1024];

	if (chdir(newcd) < 0 || !(access(newcd, W_OK | R_OK) == 0))
	{
		if (errno == EACCES)
		{
			error_msg("cd: ", newcd, \
			": Permission denied", 1);
		}
		else
			error_msg("cd: ", newcd, ": No such file or directory", 1);
		return ;
	}
	path = ft_strjoin("OLDPWD=", oldcd);
	check_export(&path, 0, 0);
	add_cd_to_env(path);
	free(path);
	getcwd(dir, (sizeof(char) * 1024));
	path = ft_strjoin("PWD=", dir);
	check_export(&path, 0, 0);
	add_cd_to_env(path);
	free(path);
	path = NULL;
	data()->error = 0;
}

void	cd_to(char *str)
{
	char	*path;
	char	dir[1024];

	path = NULL;
	getcwd(dir, (sizeof(char) * 1024));
	if (!str || str == NULL || ft_strncmp(str, "~", 1))
	{
		path = get_env_var(data()->env_p, "HOME");
		apply_cd(dir, path);
	}
	else if (ft_strncmp(str, "-", 1))
	{
		path = get_env_var(data()->env_p, "OLDPWD");
		if (path == NULL)
			error_msg("cd: ", NULL, ": OLDPWD not set", 1);
		else
		{
			printf("%s\n", path);
			apply_cd(dir, path);
		}
	}
	else
		apply_cd(dir, str);
	if (path != NULL)
		free(path);
}

int	ft_check_cd(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
		i++;
	return (i);
}

void	ft_cd(char **str)
{
	int		size;
	char	dir[1024];

	getcwd(dir, (sizeof(char) * 1024));
	size = ft_check_cd(str);
	if (size > 2)
	{
		data()->error = 1;
		error_msg("cd: ", NULL, "too many arguments", 1);
	}
	else
		cd_to(str[1]);
}
