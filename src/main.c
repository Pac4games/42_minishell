/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:01:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/11 16:14:59 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exitstts = EXIT_SUCCESS;

int	main(int ac, char **av, char **envp)
{
	t_list	*env;
//	t_tree	*root;
	(void) ac;
	(void) av;

	get_cur_env(&env, envp);
//	root->token = "ls";
//	xqt(&root, &env, 1);
	print_mtx(lst2mtx(env));
	return (g_exitstts);
}
