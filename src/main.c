/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:01:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/07 14:28:45 by paugonca         ###   ########.fr       */
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

t_data	data(void)
{
	static t_data	data;

	return (data);
}

int	main(int ac, char **av, char **envp)
{
	char	**env;

	(void)ac;
	(void)av;
	env = get_cur_env(envp);
	print_mtx(env);
	free_mtx(env);
	return (g_stts);
}
