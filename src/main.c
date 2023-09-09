/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:01:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/09 11:58:12 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stts = EXIT_SUCCESS;

void	set_exit_stts(int stts)
{
	if (WIFSIGNALED(stts))
	{
		g_stts = WTERMSIG(stts) + 128;
		if (stts == SIGINT)
			ft_putendl_fd(NULL, STDIN_FILENO);
	}
	else 
		g_stts = WEXITSTATUS(stts);
}

char	*shlvl_up(char *shlvl)
{
	char	*tmp;
	char	*res;

	tmp = ft_itoa(ft_atoi(shlvl + 6) + 1);
	res = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (res);
}

static bool	in_enter(char *in)
{
	if (!ft_strlen(in))
	{
		free(in);
		return (true);
	}
	return (false);
}

int	main(int ac, char **av, char **envp)
{
	char	*in;
	char	*prompt;

	while (true)
	{
		sig_handle(E_SIG_RL);
		prompt = ft_strjoin(SHELL, ":$ ");
		in = readline(prompt);
		free(prompt);
		sig_handle(E_SIG_IGN);
		if (in && ft_strlen(in))
			add_history(in);
		else if (!in)
		{
			ft_putstr_fd("\nexit\n", STDOUT_FILENO);
			rl_clear_history();
			exit(g_stts);
		}
		else if (ft_strlen(in))
		{
			free(in);
			continue ;
		}
	}
	return (g_stts);
}
