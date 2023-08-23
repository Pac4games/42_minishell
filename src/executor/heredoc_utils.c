/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:49:09 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/23 13:02:02 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Read the frickin' docs (family friendly 'cause of Junior)
//Takes the input for deezdocs()
static void	rtfd(int fd, char *eof, int stts)
{
	char	*in;
	char	*res;

	while (TRUE)
	{
		sig_handle(E_SIG_HDOC);
		in = readline("heredoc> ");
		if (!in)
			print_hdoc_warn(eof, in, stts);
		res = ft_strjoin(in, "\n");
		free(in);
		if (res)
		{
			if (!(ft_strlen(res) || ft_strncmp(res, eof, ft_strlen(eof))))
				break;
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
int	deezdocs(t_tree **root, t_cmd *cmd, int p)
{
	if (pipe((*root)->pipes) < 0)
		print_err("failed to open pipe", EXIT_FAILURE);
	cmd->pid = fork();
	if (cmd->pid < 0)
		print_err("failed to fork process", EXIT_FAILURE);
	else if (cmd->pid == 0)
	{
		if (p == cmd->in)
	}
}

int	is_heredoc(t_tree **root, t_cmd *cmd)
{
	int		p;
	t_tree	*tmp;

	p = 0;
	tmp = *root;
	cmd->heredoc = FALSE;
	while (tmp)
	{
		if (tmp->type == E_STDIN || tmp->type == E_HDOC)
		{
			p++;
			if (tmp->type == E_HDOC)
		}
	}
}
