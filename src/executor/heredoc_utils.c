/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:49:09 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/27 10:53:50 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//"Read The Frickin' Docs" (family friendly 'cause of Junior)
//Takes the input for deezdocs()
static void	rtfd(int fd, char *eof, int stts) //2 ok I LOVED
{
	char	*in;
	char	*res;

	while (true)
	{
		sig_handle(E_SIG_HDOC);
		in = readline("heredoc> "); // tem mesmo esse espaco?
		if (!in)
			print_hdoc_warn(eof, in, stts);
		res = ft_strjoin(in, "\n");
		free(in);
		if (res)
		{
			if (!(ft_strlen(res) || ft_strncmp(res, eof, ft_strlen(eof))))
				break ;
			if (fd > 0)
				ft_putstr_fd(res, fd);
			free(res);
		}
	}
	free(eof);
	if (res)
		free(res);
	g_stts = EXIT_SUCCESS;
	exit(g_stts);
}

//Yet another genius name (may change it later)
//It's our heredoc if it ain't obvious lol
int	deezdocs(t_tree **root, t_cmd *cmd, int p) // 2ok
{
	int	stts;

	if (pipe((*root)->pipes) < 0)
		print_err("failed to open pipe", EXIT_FAILURE);
	cmd->pid = fork();
	if (cmd->pid < 0)
		print_err("failed to fork process", EXIT_FAILURE);
	else if (cmd->pid == 0)
	{
		if (p == cmd->in)
			rtfd(((*root)->pipes)[1], ft_strjoin((*root)->content, "\n"),
				EXIT_SUCCESS);
		else
			rtfd(-1, ft_strjoin((*root)->content, "\n"), 129);
	}
	close(((*root)->pipes)[1]);
	waitpid(cmd->pid, &stts, 0);
	set_exit_stts(stts);
	if (g_stts == 129 || g_stts == 130)
	{
		if (g_stts == 129)
			g_stts = EXIT_SUCCESS;
		return (true);
	}
	return (false);
}

int	handle_hdoc(t_tree **root, t_cmd *cmd) // 2ok
{
	int		p;
	t_tree	*tmp;

	p = 0;
	tmp = *root;
	cmd->heredoc = false;
	while (tmp)
	{
		if (tmp->type == E_STDIN || tmp->type == E_HDOC)
		{
			p++;
			if (tmp->type == E_HDOC)
				if (deezdocs(&tmp, cmd, p))
					return (true);
		}
		if (!(cmd->pos))
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return (false);
}
