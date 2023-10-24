/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:10:28 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/24 13:03:34 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	term_change(void)
{
	struct termios	termios_new;

	if (tcgetattr(0, term()))
	{
		perror("");
		return ;
	}
	if (atexit(reset_the_terminal))
	{
		perror("");
		return ;
	}
	termios_new = *term();
	termios_new.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_new))
	{
		perror("");
		return ;
	}
}

//Takes the input for deezdocs()
static void	rtfd(int fd, char *eof, int stts, t_tree **root)
{
	char	*in;
	char	*res;
	
	(void)(root);
	while (true)
	{
		in = readline("> ");
		if (!in)
			print_hdoc_warn(eof, in, stts);
		res = ft_strjoin(in, "\n");
		free(in);
		if (res)
		{
			if (!ft_strlen(res) || !ft_strncmp(res, eof, ft_strlen(eof)))
				break ;
			if (*num_cmds() > 0 && fd > 0)
				ft_putstr_fd(res, fd);
			free(res);
		}
	}
	free(eof);
	if (res)
		free(res);
	*exit_stts() = EXIT_SUCCESS;
	/*if (*num_cmds()>0 )
		fodase3(root);*/
	for(int i = 3; i < FOPEN_MAX; i++)
		close(i);
	exit(*exit_stts());
}

//Yet another genius name (may change it later)
//It's our heredoc if it ain't obvious lol
static int	deezdocs(t_tree **root, t_cmd *cmd, int p, int stts)
{
	if (*num_cmds()>0 && pipe((*root)->pipes) < 0)
		print_err("failed to open pipe", EXIT_FAILURE);
	cmd->pid = fork();
	if (cmd->pid < 0)
		print_err("failed to fork process", EXIT_FAILURE);
	else if (cmd->pid == 0)
	{
		signal_here();
		if (p == cmd->in)
			rtfd(((*root)->pipes)[1], ft_strjoin((*root)->content, "\n"),
				EXIT_SUCCESS, root);
		else
			rtfd(-1, ft_strjoin((*root)->content, "\n"), 129, root);
	}
	if (*num_cmds()>0 )
	{
		//<< ola | cat Makefile > lingua
		for(int i = 3; i < FOPEN_MAX; i++)
			close(i);
	}
		//close(((*root)->pipes)[1]);
	waitpid(cmd->pid, &stts, 0);
	sig_handle();
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
	*is_inside() = -1;
	while (tmp)
	{
		term_change();
		if (tmp->type == E_STDIN || tmp->type == E_HDOC)
		{
			p++;
			if (tmp->type == E_HDOC)
				if (deezdocs(&tmp, cmd, p, 0))
					return (1);
		}
		if (!(cmd->pos))
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return (0);
}
