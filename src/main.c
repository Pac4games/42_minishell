/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:01:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/24 20:16:45 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_stts(int stts)
{
	if (WIFSIGNALED(stts))
	{
		*exit_stts() = WTERMSIG(stts) + 128;
		if (stts == SIGINT)
			ft_putendl_fd(NULL, STDIN_FILENO);
	}
	else
		*exit_stts() = WEXITSTATUS(stts);
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

static void	le_loop(char *in, char *prompt, char **env, t_tree *tree)
{
	while (true)
	{
		rl_catch_signals = 0;
		sig_handle();
		prompt = ft_strjoin(SHELL, ":$ ");
		in = readline(prompt);
		free(prompt);
		if (in && ft_strlen(in))
			add_history(in);
		else if (!in)
		{
			ft_putstr_fd("\nexit\n", STDOUT_FILENO);
			rl_clear_history();
			*exit_stts() = EXIT_FAILURE;
			exit(*exit_stts());
		}
		else if (!ft_strlen(in))
		{
			free(in);
			continue ;
		}
		parsa(in, &env, &tree, 0);
		if (*num_cmds() > 1){
			// fodase2(get_tree_root(&tree));
			fodase3(get_tree_root(&tree));
		}
		free_tree(get_tree_root(&tree));
		for (int i = 3;i < FOPEN_MAX; i++)
			close (i);
		*num_cmds() = 0;
		*syntax() = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*in;
	char	*prompt;
	char	**env;
	t_tree	*tree;

	(void)av;
	if (ac != 1)
		print_err("invalid number of arguments", EXIT_FAILURE);
	in = NULL;
	prompt = NULL;
	env = get_cur_env(envp);
	tree = NULL;
	*syntax() = 0;
	*exit_stts() = EXIT_SUCCESS;
	le_loop(in, prompt, env, tree);
	return (*exit_stts());
}
