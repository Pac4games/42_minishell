/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:16:15 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/11 11:05:10 by paugonca         ###   ########.fr       */
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
		free_mtx(env_mtx);
		g_exitstts = 126;
		exit(g_exitstts);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Command not found", STDERR_FILENO);
		free_mtx(env_mtx);
		g_exitstts = 127;
		exit(g_exitstts);
	}
	return (cmd);
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
	if (path)
		free(path);
	while (env_tmp)
	{
		path = get_cur_path(env_tmp->content, cmd);
		if (is_valid_path(cmd, path))
			return (path);
		free(path);
		env_tmp = env_tmp->next;
	}
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": Command not found", STDERR_FILENO);
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_list *env, char **env_mtx)
{
	if (cmd[0] == '/')
		return (get_abs_path(cmd, env_mtx));
	else
		return (get_rel_path(cmd, env));
}
