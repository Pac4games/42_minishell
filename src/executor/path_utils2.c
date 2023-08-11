/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:38:21 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/11 15:07:24 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_path(char *cmd, char *path)
{
	struct stat	tmp;

	if (!path)
		return (0);
	ft_memset(&tmp, 0, sizeof(stat));
	lstat(path, &tmp);
	if (S_ISDIR(tmp.st_mode))
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(" is a directory", STDERR_FILENO);
		exit(126);
	}
	if (access(path, X_OK) < 0)
		return (0);
	return (1);
}

char	*format_program_path(char *cmd, char *path, char *tmp)
{
	path = getcwd(NULL, 0);
	tmp = ft_strjoin(cmd, "/");
	free(path);
	path = ft_strjoin(cmd, tmp);
	free(tmp); 
	if (is_valid_path(cmd, path))
		return (path);
	return (NULL);
}

static char	*get_cur_path_fr(char **path, char *cmd)
{
	char	*tmp;
	int		p;

	tmp = NULL;
	p = 0;
	while (path[p])
	{
		tmp = ft_strjoin(path[p], cmd);
		if (is_valid_path(cmd, tmp))
		{
			free_mtx(path);
			free(cmd);
			return (tmp);
		}
		free(tmp);
	}
	free_mtx(path);
	free(cmd);
	return (NULL);
}

//Only gets called to look for relative path, returns NULL if absolute
//path is found.
char	*get_cur_path(char *env, char *cmd)
{
	char	**tmp_path;
	char	*tmp_cmd;

	tmp_path = NULL;
	tmp_cmd = NULL;
	if (ft_strncmp(env, "PATH=", 5))
		return (NULL);
	tmp_path = ft_split(env, ':');
	tmp_cmd = ft_strjoin("/", cmd);
	return (get_cur_path_fr(tmp_path, tmp_cmd));
}
