/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:39:32 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/20 18:34:32 by dcarvalh         ###   ########.fr       */
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

// static void	sig_rl(int sig, siginfo_t *info, void *ucontext)
// {
// 	(void)info;
// 	(void)ucontext;
// 	printf("---%d--\n", *is_inside());
// 	if (sig == SIGQUIT)
// 	{
// 		*exit_stts() = 131;
// 		ft_putstr_fd("", 2);
// 	}
// 	else if (sig == SIGINT)
// 	{
// 		*exit_stts() = 130;
// 		ft_putstr_fd("^C\n", 0);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// static void	sig_hdoc(int sig, siginfo_t *info, void *ucontext)
// {
// 	(void)info;
// 	(void)ucontext;
// 	if (sig == SIGQUIT)
// 		return ;
// 	else if (sig == SIGINT)
// 	{
// 		ft_putendl_fd(NULL, 0);
// 		unlink(".heredoc_tmp");
// 		*exit_stts() = 130;
// 		exit(*exit_stts());
// 	}
// }

// static void	sig_check(struct sigaction *sa, t_sigtype type)
// {
// 	ft_memset(sa, 0, sizeof(*sa));
// 	sa->sa_flags = SA_SIGINFO;
// 	sigemptyset(&sa->sa_mask);
// 	if (type == E_SIG_IGN)
// 		(sa->sa_handler) = SIG_IGN;
// 	else if (type == E_SIG_DFL)
// 		(sa->sa_handler) = SIG_DFL;
// 	else if (type == E_SIG_RL)
// 		(sa->sa_sigaction) = sig_rl;
// 	else if (type == E_SIG_HDOC)
// 		(sa->sa_sigaction) = sig_hdoc;
// 	else
// 		return ;
// }

// void	sig_handle(t_sigtype type)
// {
// 	struct sigaction	sa;

// 	sig_check(&sa, type);
// 	if (sigaction(SIGQUIT, &sa, NULL) < 0 || sigaction(SIGINT, &sa, NULL) < 0)
// 		exit(EXIT_FAILURE);
// }

// static void	ft_handler(int sig)
// {

// 	if (sig == SIGINT)
// 	{
// 		*exit_stts() = 130;
// 		ft_putstr_fd("^C\n", 0);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else if (sig == SIGQUIT)
// 	{
		
// 		*exit_stts() = 131;
// 		ft_putstr_fd("", 2);
// 	}
// }


void	ctrl_c(int sig)
{
	(void)sig;
	*exit_stts() = 130;
	if (*is_inside() > 0)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (!*is_inside())
	{
		write(2, "^C\n", 3);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_bs(int sig)
{
	(void)sig;
	if (*is_inside() < 1)
		SIG_IGN ;
	else
	{
		*exit_stts() = 131;
		printf("Quit (core dumped)\n");
	}
}

void	sig_handle(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
}

void	here_c(int sig)
{
	(void)sig;
	write(2, "^C\n", 3);
	exit(*exit_stts());
}

void	signal_here(void) 
{
	signal(SIGINT, here_c);
	signal(SIGQUIT, SIG_IGN);
}