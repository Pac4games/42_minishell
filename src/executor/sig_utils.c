/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:44:55 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/27 10:54:00 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sig_rl(int sig, siginfo_t *info, void *ucontext) // 2 poderia me dar uma breve explicacao sobre essa funcao?
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		g_stts = 130;
		rl_replace_line("", 0);
		ft_putendl_fd(NULL, STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sig_hdoc(int sig, siginfo_t *info, void *ucontext) //2 pipe?
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		ft_putendl_fd(NULL, 0);
		unlink(".heredoc_tmp");
		g_stts = 130;
		exit(g_stts);
	}
}

static void	sig_check(struct sigaction *sa, t_sigtype type) // ok2, unica duvida esta para hdoc
{
	ft_memset(sa, 0, sizeof(*sa));
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	if (type == E_SIG_IGN)
		(sa->sa_handler) = SIG_IGN;
	else if (type == E_SIG_DFL)
		(sa->sa_handler) = SIG_DFL;
	else if (type == E_SIG_RL)
		(sa->sa_sigaction) = sig_rl;
	else if (type == E_SIG_HDOC)
		(sa->sa_sigaction) = sig_hdoc;
	else
		return ;
}

void	sig_handle(t_sigtype type) // 2ok
{
	struct sigaction	sa;

	sig_check(&sa, type);
	if (sigaction(SIGQUIT, &sa, NULL) < 0 || sigaction(SIGINT, &sa, NULL) < 0)
		exit(EXIT_FAILURE);
}
