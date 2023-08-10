/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/10 12:55:43 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//My own libft
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

//Command struct
typedef struct s_cmd
{
	char	*path;
	char	**args;
	int		pid;
	int		fd[2];
}			t_cmd;

//Binary Tree struct (also known as Command Table)
typedef struct s_node
{
	t_cmd			*data;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
}			t_node;

/*					   SRC						*/
//extra_utils.c
void	free_matrix(char **mtx);
void	print_matrix(char **mtx);
//env_utils.c
void	get_cur_env(t_list **env, char **envp);

/*					EXECUTOR					*/

#endif
