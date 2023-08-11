/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/11 13:52:00 by paugonca         ###   ########.fr       */
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

//Global variable (put here so LSP auto-correction can detect it)
int g_exitstts = EXIT_SUCCESS;

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
	int				fds[2];
}			t_tree;

/*					   SRC						*/
//extra_utils.c
void	free_mtx(char **mtx);
void	print_mtx(char **mtx);
char	**lst2mtx(t_list *lst);
//env_utils.c
void	get_cur_env(t_list **env, char **envp);
void	print_env(t_list *env, int fd);

/*					EXECUTOR					*/
//xqt.c
void	xqt(t_tree **root, t_list **env, int cmd_num);
//path_utils1.c
char	*get_cmd_path(char *cmd, t_list *env, char **env_mtx);
//path_utils2.c
int		is_valid_path(char *cmd, char *path);
char	*format_program_path(char *cmd, char *path, char *tmp);
char	*get_cur_path(char *env, char *cmd);

#endif
