/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/14 15:43:11 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Pac4's libft
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
//The readline library may not come installed by default. The package on
//Ubuntu is called "libreadline-dev", while on Fedora it's
//"readline-devel".
# include <readline/readline.h>
# include <readline/history.h>

//Booleans
# define TRUE 1
# define FALSE 0

//Shell name
# define SHELL "minihell"

//Global variable declaration
int	g_stts;

//Node types
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
	int		pipes[2];
	int		num;
	int		fd;
	int		in;
	int		out;
	int		doc;
	char	***env;
	pid_t	pid;
}			t_cmd;

//Binary Tree struct (also known as Command Table)
typedef struct s_tree
{
	char			*input;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
	enum e_ndtype	type;
	int				fds[2];
	int				id;
	int				pipe_num;
}			t_tree;

/*					   SRC						*/
//extra_utils.c
void	free_mtx(char **mtx);
void	print_mtx(char **mtx);
void	print_err(char *msg, int stts);
void	print_shell_err(char *cmd, char *msg, int stts);

/*					EXECUTOR					*/
//xqt.c
void	xqt(t_tree **root, t_cmd *cmd, int *fd);
//env_utils.c
char	**get_cur_env(char **env);

#endif
