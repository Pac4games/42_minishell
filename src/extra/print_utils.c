/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:50:37 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/28 10:37:24 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_mtx(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		ft_putendl_fd(mtx[p++], STDOUT_FILENO);
}

void	print_err(char *msg, int stts) // 2ok
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_stts = stts;
	exit(g_stts);
}

void	print_shell_err(char *cmd, char *msg, int stts) // 2ok
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	free(cmd);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	if (stts != NO_EXIT)
	{
		g_stts = stts;
		exit(g_stts);
	}
}

void	print_hdoc_warn(char *eof, char *in, int stts) // 2 breve explicacao
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(": warning: here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
	free(eof);
	free(in);
	unlink(".heredoc_tmp");
	g_stts = stts;
	exit(g_stts);
}

void	print_syntax_error(void) //2ok mudou syntax
{
	if ((*syntax()) == 1)
		ft_putendl_fd("Syntax Error", STDOUT_FILENO);
	g_stts = EXIT_FAILURE;
	(*syntax())++;
	printf("syntax vale %ls\n", syntax());
}
