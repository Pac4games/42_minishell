/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:16:15 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/11 09:53:58 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_abs_path(char *cmd, char **env_mtx)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(" is a directory", STDERR_FILENO);
		free_matrix(env_mtx);
		g_exitstts = 126;
		exit(g_exitstts);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Command not found", STDERR_FILENO);
		free_matrix(env_mtx);
		g_exitstts = 127;
		exit(g_exitstts);
	}
	return (cmd);
}

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
		g_exitstts = 126;
		exit(g_exitstts);
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
	free(path); 
	return (path);
}

char	*get_rel_path(char *cmd, t_list *env)
{
	char	*path;
	char	*tmp;
	t_list	*env_tmp;
	path = NULL;
	tmp = NULL;
	env_tmp = env;
	if (cmd[0] == '.')
		return (format_program_path(cmd, path, tmp));
}

char	*get_cmd_path(char *cmd, t_list *env, char **env_mtx)
{
	if (cmd[0] == '/')
		return (get_abs_path(cmd, env_mtx));
	else
		return (get_rel_path(cmd, env));
}
