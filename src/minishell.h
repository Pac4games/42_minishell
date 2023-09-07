/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/07 14:32:37 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Pac4's libft
# include "../libft/libft.h"
# include "parse.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
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
//0 - special file permissions (none in this case)
//6 - user permissions (read + write)
//4 - group permissions (read)
//4 - others permissions (read)
# define S_STDPERMS 0644

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

//Data struct (mostly used for parsing)
typedef struct s_data
{
	int			nbr_tokens;
	char		**tokens;
	char		*str_cmd;
	char		**env_p;
	char		***cmds;
	int			fd[2][2];
	int			curr_cmd;
	int			curr_fd;
	int			count;
	int			warning;
	int			shlvl;
	char		**here_doc;
	char		*str_tmp;
	int			error;
}			t_data;

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

//main.c
void			set_exit_stts(int stts);
char			*shlvl_up(char *shlvl);

/*					EXECUTOR					*/
//executor.c
void			xqt(t_tree *root, t_cmd *cmd, int *fd);
//cmd_utils.c
char			*get_cmd(t_tree *node, int pos);
char			**get_cmd_args(t_tree *node, int pos);
int				get_cmd_num(t_tree *node);
//env_utils.c
char			**get_cur_env(char **env);
//path_utils.c
char			*get_cmd_path(char *cmd, char **env);
//sig_utils.c
void			sig_handle(t_sigtype type);
//redir_utils.c
int				get_redir_num(t_tree *node, int pos, t_io io);
void			redir(t_tree *node, t_cmd *cmd, int *fd);
//redir_in_utils.c
void			redir_in(t_tree *node, t_cmd *cmd, int in_num);
//redir_out_utils.c
void			redir_out(t_tree *node, t_cmd *cmd, int out_num);
int				redir_hdoc(t_tree **root, t_cmd *cmd);
//heredoc_utils.c
int				handle_hdoc(t_tree **root, t_cmd *cmd);
int				deezdocs(t_tree **root, t_cmd *cmd, int p);

// ---------- BUILTINS ------------

// check_builtins
int				is_builtins(char *cmd);
void			call_builtins(char **cmd);
void			clean_exit_child(void);

// error_msg
void			error_msg(char *option, char *var_option, \
				char *msg, int err);
void			check_permission(void);
void			error_exec(void);
void			free_all(void);
void			exit_child(void);

//  ft_cd
void			add_cd_to_env(char *path);
void			apply_cd(char *oldcd, char *newcd);
void			cd_to(char *str);
int				ft_check_cd(char **str);
void			ft_cd(char **str);

// ft_echo
int				is_flag(char *str);
void			print_echo(char **str, int flag);
void			ft_echo_beg(char **str, int flag);
void			ft_echo(char **str);

// ft_env
void			ft_env(char **str);
void			ft_env_exec(char **str);

// ft_exit
int				ft_exit_err(void);
long long int	ft_atoli_checker(char *nptr, int i, int sing);
long long int	ft_atoli(char *nptr);
void			ft_exit(char **str);

// ft_export
void			export_declare_exec(char **str);
void			export_declare(void);
void			check_env_name(char **env, char *str, int size);
int				check_export(char **str, int i, int j);
void			ft_export(void);

// ft_pwd
void			ft_pwd(char **str);
void			ft_pwd_exec(char **str);

// ft_unset
void			ft_unset(char **str, char *find);
void			unset_var(char **env, int skip);

/*					 EXTRA						*/
//print_utils.c
void			print_mtx(char **mtx);
void			print_err(char *msg, int stts);
void			print_shell_err(char *cmd, char *msg, int stts);
void			print_hdoc_warn(char *eof, char *in, int stts);
//free_utils.c
void			free_mtx(char **mtx);
void			free_tree(t_tree **node);
t_tree			**get_tree_root(t_tree **node);
//data_utils.c
t_data			data(void);

#endif
