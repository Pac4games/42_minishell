/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:16:15 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/11 00:14:35 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

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
		exitstts = 126;
		exit(exitstts);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Command not found", STDERR_FILENO);
		free_matrix(env_mtx);
		exitstts = 127;
		exit(exitstts);
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
}

char	*get_cmd_path(char *cmd, t_list *env, char **env_mtx)
{
	if (cmd[0] == '/')
		return (get_abs_path(cmd, env_mtx));
	else
		return (get_rel_path(cmd, env));
}
