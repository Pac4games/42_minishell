/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:44:55 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/21 15:52:35 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sig_check(struct sigaction *sa, t_sigtype type)
{
	ft_memset(sa, 0, sizeof(*sa));
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	if (type == E_SIG_IGN)
		(sa->sa_handler) = SIG_IGN;
	else if (type == E_SIG_DFL)
		(sa->sa_handler) = SIG_DFL;
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
