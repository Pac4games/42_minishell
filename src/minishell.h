/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/23 12:52:35 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Pac4's libft
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
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

//Standard permissions for new files in Unix-based/like systems
//User - read and write
//Group - read
//Others - read
# define S_STDPERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

//Standard flags for outfile creation
//O_TRUNC will delete any contents inside the file if it exists
# define O_STDOUTFILE (O_CREAT | O_WRONLY | O_TRUNC)

//Standard flags for output appending
# define O_STDAPPEND (O_CREAT | O_WRONLY | O_APPEND)

//Global variable declaration
extern int	g_stts;

//Node types
typedef enum e_ndtype
{
	E_ARG,
	E_PIPE,
	E_FLAG,
	E_STDIN,
	E_HDOC,
	E_STDOUT,
	E_APPEND,
	E_BUILTIN,
	E_CMD
}			t_ndtype;

//Input/Output (I/O)
typedef enum e_io
{
	E_IN,
	E_OUT
}			t_io;

//Signal types
typedef enum e_sigtype
{
	E_SIG_IGN,
	E_SIG_DFL,
	E_SIG_RL,
	E_SIG_HDOC
}			t_sigtype;

//Command struct
typedef struct s_cmd
{
	pid_t	pid;
	int		pipes[2];
	int		pos;
	int		num;
	int		fd;
	int		in;
	int		out;
	int		heredoc;
	char	***env;
}			t_cmd;

//Binary Tree struct (also known as Command Table)
typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
	enum e_ndtype	type;
	char			*content;
	int				pipes[2];
	int				pipe_num;
}			t_tree;

/*					EXECUTOR					*/
//executor.c
void	xqt(t_tree *root, t_cmd *cmd, int *fd);
//cmd_utils.c
char	*get_cmd(t_tree *node, int pos);
char	**get_cmd_args(t_tree *node, int pos);
int		get_cmd_num(t_tree *node);
//env_utils.c
char	**get_cur_env(char **env);
//path_utils.c
char	*get_cmd_path(char *cmd, char **env);
//sig_utils.c
void	sig_handle(t_sigtype type);
//redir_utils.c
int		get_redir_num(t_tree *node, int pos, t_io io);
void	redir(t_tree *node, t_cmd *cmd, int *fd);
//redir_in_utils.c
void	redir_in(t_tree *node, t_cmd *cmd, int in_num);
//redir_out_utils.c
void	redir_out(t_tree *node, t_cmd *cmd, int out_num);
int		redir_heredoc(t_tree **root, t_cmd *cmd);
//heredoc_utils.c
int		is_heredoc(t_tree **root, t_cmd *cmd);
int		deezdocs(t_tree **root, t_cmd *cmd, int p);

/*					 EXTRA						*/
//print_utils.c
void	print_mtx(char **mtx);
void	print_err(char *msg, int stts);
void	print_shell_err(char *cmd, char *msg, int stts);
void	print_hdoc_warn(char *eof, char *in, int stts);
//free_utils.c
void	free_mtx(char **mtx);
void	free_tree(t_tree **node);
t_tree	**get_tree_root(t_tree **node);

#endif
