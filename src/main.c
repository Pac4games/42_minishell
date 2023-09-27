/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:01:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/27 08:28:39 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stts = EXIT_SUCCESS;

void	set_exit_stts(int stts)// ok
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

char	*shlvl_up(char *shlvl) // ok
{
	char	*tmp;
	char	*res;

	tmp = ft_itoa(ft_atoi(shlvl + 6) + 1);
	res = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (res);
}

static void	le_loop(char *in, char *prompt, char **env, t_tree *tree) // duvidas
{
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
			g_stts = EXIT_FAILURE;
			exit(g_stts);
		}
		else if (!ft_strlen(in))
		{
			free(in);
			continue ;
		}
		parsa(in, &env, &tree, 0);
		free_tree(get_tree_root(&tree));
		*syntax() = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*in;
	char	*prompt;
	char	**env;
	t_tree	*tree;

	(void)ac;
	(void)av;
	in = NULL;
	prompt = NULL;
	env = get_cur_env(envp);
	tree = NULL;
	*syntax() = 0; // ?
	le_loop(in, prompt, env, tree);
	return (g_stts);
}
