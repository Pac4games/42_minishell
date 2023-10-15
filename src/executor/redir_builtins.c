/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:17 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/10 13:11:32 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_builtin_in(t_tree *node)
{
	int	fd;

	while (node)
	{
		if (node->type == E_STDIN)
		{
			fd = open(node->content, O_RDONLY, S_STDPERMS);
			if (fd == -1)
				return (print_builtin_err(node->content));
			close(fd);
		}
		node = node->left;
	}
	return (1);
}

int	redir_builtin_in(t_tree *node)
{
	pid_t	pid;
	int		stts;

	if (!get_redir_num(node, 0, E_IN))
		return (0);
	pid = fork();
	if (pid < 0)
		print_err("failed to fork process", EXIT_FAILURE);
	if (pid == 0)
		exit(open_builtin_in(node));
	waitpid(pid, &stts, 0);
	*exit_stts() = WEXITSTATUS(stts);
	if (*exit_stts() == 255)
		*exit_stts() = EXIT_FAILURE;
	else
		*exit_stts() = EXIT_SUCCESS;
	return (*exit_stts());
}

int	redir_builtin_out(t_tree *node)
{
	t_cmd	cmd;
	int		i;
	int		fd;

	cmd.out = get_redir_num(node, 0, E_OUT);
	i = 0;
	while (node)
	{
		if (node->type == E_STDOUT || node ->type == E_APPEND)
		{
			if (node->type == E_STDOUT)
				fd = open(node->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(node->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
			i++;
			if (fd == -1)
				return (print_builtin_err(node->content));
			if (i != cmd.out)
				close(fd);
			else
				dup2(fd, STDOUT_FILENO);
		}
		node = node->left;
	}
	return (1);
}
