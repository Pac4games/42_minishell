/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:39:32 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/17 17:13:18 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_set_termios(void)
{
	struct termios	term;
	struct termios	termbase;

	if (tcgetattr(STDIN_FILENO, &term) != 0 || \
	tcgetattr(STDIN_FILENO, &termbase) != 0)
		print_err("failed to get terminal attributes", EXIT_FAILURE);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
}

static void	sig_rl(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
	{
		*exit_stts() = 131;
		ft_putstr_fd("", 2);
	}
	else if (sig == SIGINT)
	{
		*exit_stts() = 130;
		ft_putstr_fd("^C\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sig_hdoc(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		ft_putendl_fd(NULL, 0);
		unlink(".heredoc_tmp");
		*exit_stts() = 130;
		exit(*exit_stts());
	}
}

static void	sig_check(struct sigaction *sa, t_sigtype type)
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

void	sig_handle(t_sigtype type)
{
	struct sigaction	sa;

	sig_check(&sa, type);
	if (sigaction(SIGQUIT, &sa, NULL) < 0 || sigaction(SIGINT, &sa, NULL) < 0)
		exit(EXIT_FAILURE);
}
/*
static void	ft_handler(int sig)
{

	if (sig == SIGINT)
	{
		*exit_stts() = 130;
		ft_putstr_fd("^C\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		
		*exit_stts() = 131;
		ft_putstr_fd("", 2);
	}
}

void    handle_signals(void)
{
    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handler);
}*/