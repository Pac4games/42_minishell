/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:24:00 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/14 15:25:18 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_abs_path(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		print_shell_err(cmd, "Is a directory", 126);
	}
	else if (access(cmd, X_OK) < 0)
		print_shell_err(cmd, "command not found", 127);
	return (cmd);
}

static char	*get_rel_path(char *cmd, char **env, int p)
{
	char	*tmp;
	char	*pwd;
	char	*cwd;

	if (cmd[0] && cmd[0] == '.')
	{
		cwd = getcwd(NULL, 0);
		pwd = ft_strjoin(cwd, "/");
		free(cwd);
		tmp = ft_strjoin(pwd, cmd);
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **env)
{
	if (!cmd)
		return (NULL);
	if (ft_strlen(cmd) == 1 && cmd[0] == '.')
	{
		ft_putstr_fd(SHELL, STDERR_FILENO);
		ft_putendl_fd(": filename argument required", STDERR_FILENO);
		ft_putendl_fd(".: usage: . filename [arguments]", STDERR_FILENO);
		g_stts = 126;
		exit(g_stts);
	}
	else if (ft_strlen(cmd) == 2 && cmd[0] == '.' && cmd[1] == '.')
		print_shell_err(cmd, "command not found", 127);
	else if (cmd[0] == '/')
		return (get_abs_path(cmd));
}
