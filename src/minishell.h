/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/10 14:23:30 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Pac4's libft
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

//Node types, pretty self explanatory
enum e_ndtype
{
	E_PIPE,
	E_LESS,
	E_LLESS,
	E_GREATER,
	E_GGREATER,
	E_BUILTIN,
	E_CMD
};

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
	t_cmd			*cmd;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
	enum e_ndtype	type;
}			t_node;

/*					   SRC						*/
//extra_utils.c
void	free_matrix(char **mtx);
void	print_matrix(char **mtx);
//env_utils.c
void	get_cur_env(t_list **env, char **envp);

/*					EXECUTOR					*/

#endif
