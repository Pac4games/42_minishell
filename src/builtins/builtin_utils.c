/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:19:06 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/29 16:37:29 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_builtin_err(char *arg) // 2ok
{
	ft_putstr_fd("Error: couldn't open file: ", STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
	free(arg);
	return (-1);
}

int	run_builtin(t_tree *node, char ***env, char *cmd, int fd) //2 ok
{
	if (cmd && !ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "exit", 5))
		return (ft_exit(get_cmd_args(node, 0)));
	if (cmd && !ft_strncmp(cmd, "echo", 5))
		return (ft_echo(get_cmd_args(node, 0), fd));
	if (cmd && !ft_strncmp(cmd, "env", 4))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "export", 7))
		return (ft_export(get_cmd_args(node, 0), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", 6))
		return (ft_unset(get_cmd_args(node, 0), env));
	if (cmd && !ft_strncmp(cmd, "cd", 3))
		return (ft_cd(get_cmd_args(node, 0), env));
	if (fd > 2)
		close(fd);
	return (0);
}

bool	is_builtin(t_tree *node, char ***env, char *cmd) // 2ok
{
	int	fd;
	printf("cmd eh %s\n", cmd);
	if (cmd && (!ft_strncmp(cmd, "pwd", 4)
			|| !ft_strncmp(cmd, "exit", 5)
			|| !ft_strncmp(cmd, "echo", 5) 
			|| !ft_strncmp(cmd, "env", 4)
			|| !ft_strncmp(cmd, "export", 7)
			|| !ft_strncmp(cmd, "unset", 6)
			|| !ft_strncmp(cmd, "cd", 3)))
	{
		printf("eh cmd\n");
		if (redir_builtin_in(node))
		{
			printf("\ntrue\n");
			return (true);
		}
		fd = redir_builtin_out(node);
		printf("fd eh %d\n", fd);
		run_builtin(node, env, cmd, fd);
		printf("eh true\n");
		return (true);
	}
	printf("nao eh cmd\n");
	return (false);
}

int	builtin_ret(t_tree *node, char ***env, char *cmd, int pos) //2 ok
{
	int	fd;

	fd = STDOUT_FILENO;
	if (cmd && !ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "exit", 5))
		return (ft_exit(get_cmd_args(node, pos)));
	if (cmd && !ft_strncmp(cmd, "echo", 5))
		return (ft_echo(get_cmd_args(node, pos), fd));
	if (cmd && !ft_strncmp(cmd, "env", 4))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "export", 7))
		return (ft_export(get_cmd_args(node, pos), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", 6))
		return (ft_unset(get_cmd_args(node, pos), env));
	if (cmd && !ft_strncmp(cmd, "cd", 3))
		return (ft_cd(get_cmd_args(node, pos), env));
	return (0);
}
