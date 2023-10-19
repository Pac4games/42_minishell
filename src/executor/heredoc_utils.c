/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:38:57 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/16 17:15:43 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Takes the input for deezdocs()
static void	rtfd(int fd, char *eof, int stts)
{
	char	*in;
	char	*res;

	while (true)
	{
		handle_signals();
		in = readline("> ");
		if (!in)
			print_hdoc_warn(eof, in, stts);
		res = ft_strjoin(in, "\n");
		free(in);
		if (res)
		{
			if (!ft_strlen(res) || !ft_strncmp(res, eof, ft_strlen(eof)))
				break ;
			if (fd > 0)
				ft_putstr_fd(res, fd);
			free(res);
		}
	}
	free(eof);
	if (res)
		free(res);
	*exit_stts() = EXIT_SUCCESS;
	exit(*exit_stts());
}

//Yet another genius name (may change it later)
//It's our heredoc if it ain't obvious lol
int	deezdocs(t_tree **root, t_cmd *cmd, int p)
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
	if (*exit_stts() == 129 || *exit_stts() == 130)
	{
		if (*exit_stts() == 129)
			*exit_stts() = EXIT_SUCCESS;
		return (1);
	}
	return (0);
}

int	handle_hdoc(t_tree **root, t_cmd *cmd)
{
	int		p;
	t_tree	*tmp;

	p = 0;
	tmp = *root;
	cmd->heredoc = 0;
	while (tmp)
	{
		if (tmp->type == E_STDIN || tmp->type == E_HDOC)
		{
			p++;
			if (tmp->type == E_HDOC)
				if (deezdocs(&tmp, cmd, p))
					return (1);
		}
		if (!(cmd->pos))
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return (0);
}
