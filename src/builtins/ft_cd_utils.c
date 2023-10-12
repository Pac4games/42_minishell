/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:49:32 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/12 11:43:49 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//If "cd" receives no arguments, it will navigate to the current user's
//home directory. Otherwise, if "cd" is followed by a single or two "-", it
//will navigate to the working directory before the last time that "cd" was
//called.
int	ft_cd_weird_args(char **args, char ***env)
{
	char	*tmp;

	tmp = NULL;
	if (mtx_len(args) == 1 || (mtx_len(args) == 2 && args[1][1] == '-' && args[1][0] =='-'))
	{
		tmp = parse_signs(ft_strdup("$HOME"), *env);
		chdir(tmp);
	}
	else if (((args[1][0] == '-') || !ft_strncmp(args[1], "--", 2)) && \
	ft_strlen(args[1]) < 2)
	{
		tmp = parse_signs(ft_strdup("$OLDPWD"), *env);
		ft_putendl_fd(tmp, STDOUT_FILENO);
		chdir(tmp);
	}
	if (tmp)
	{
		free_mtx(args);
		free(tmp);
		return (1);
	}
	return (0);
}
