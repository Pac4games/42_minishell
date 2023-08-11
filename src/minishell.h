/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/10 23:04:52 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Pac4's libft
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>

//Global variable (put here so LSP auto-correction can detect it)
int exitstts = EXIT_SUCCESS;

//Node types, pretty self explanatory
typedef enum e_ndtype
{
	E_PIPE,
	E_LESS,
	E_LLESS,
	E_GREATER,
	E_GGREATER,
	E_BUILTIN,
	E_CMD
}			t_ndtype;

//Command struct
typedef struct s_cmd
{
	int		num;
	int		pid;
	int		fd;
	int		in;
	int		out;
	int		doc;
	t_list	*env;
}			t_cmd;

//Binary Tree struct (also known as Command Table)
typedef struct s_tree
{
	void			*token;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
	enum e_ndtype	type;
	int				fd[2];
}			t_tree;

/*					   SRC						*/
//extra_utils.c
void	free_matrix(char **mtx);
void	print_matrix(char **mtx);
char	**lst2mtx(t_list *env);
//env_utils.c
void	get_cur_env(t_list **env, char **envp);
void	print_env(t_list *env, int fd);

/*					EXECUTOR					*/

#endif
