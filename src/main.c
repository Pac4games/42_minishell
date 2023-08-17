/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:01:34 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/17 14:35:58 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stts = EXIT_SUCCESS;

int	main(int ac, char **av, char **envp)
{
	char	**env;

	(void) ac;
	(void) av;
	env = get_cur_env(envp);
	print_mtx(env);
	free_mtx(env);
	return (g_stts);
}
