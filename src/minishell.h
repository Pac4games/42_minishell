/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/09 20:53:17 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Pac4's libft
# include "../libft/libft.h"
# include "parse.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
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

//Shell name
# define SHELL "MiniHell"

//Macro for print_shell_err() not quitting the program
# define NO_EXIT 69420

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

//Exclusively used by add_var()
typedef struct s_var
{
	int		start;
	int		end;
	int		i;
	int		j;
	char	*str;
	char	*var;
	char	**res;
}			t_var;

//main.c
void			set_exit_stts(int stts);
char			*shlvl_up(char *shlvl);
//env_utils.c
char			**get_cur_env(char **env);
char			*get_env_var(char **env, char *var_name);

/*					 PARSER						*/
//syntax_utils.c
int				*syntax(void);
//get_stts_utils.c
char			*get_stts(char *str, int i, char *val);
//var_utils.c
bool			is_var(char c);
char			*add_var(char *str, char *var, int start, int end);
char			*find_var(char *var, char **env);
char			*get_var(char *str, int *i, char **env);
//signs_utils.c
int				find_eq_sign(char *str);
char			*parse_signs(char *str, char **env);
//quote_utils.c
bool			is_diff_sign(char *sign, char c);
int				skip_quotes(char *str, int i);

/*					EXECUTOR					*/
//executor.c
void			xqt(t_tree *root, t_cmd *cmd, int *fd);
//cmd_utils.c
char			*get_cmd(t_tree *node, int pos);
char			**get_cmd_args(t_tree *node, int pos);
int				get_cmd_num(t_tree *node);
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

/*				   BUILTINS					*/
//buitin_utils.c
int				is_builtin(t_tree *node, char ***env, char *cmd, int pos);
//ft_pwd.c
int				ft_pwd(int fd);
//ft_exit.c
int				ft_exit(char **args);
//ft_echo.c
int				ft_echo(char **args, int fd);
//ft_env.c
int				ft_env(char **env, int fd);
//ft_export.c
int				ft_export(char **args, char ***env, int fd);
//export_utils.c
void			export_arg_new(char *arg, char ***env, int i);
//ft_cd.c
int				ft_cd(char **args, char ***env);

/*					 EXTRA						*/
//print_utils.c
void			print_mtx(char **mtx);
void			print_err(char *msg, int stts);
void			print_shell_err(char *cmd, char *msg, int stts);
void			print_hdoc_warn(char *eof, char *in, int stts);
void			print_syntax_error(void);
//free_utils.c
void			free_mtx(char **mtx);
void			free_tree(t_tree **node);
t_tree			**get_tree_root(t_tree **node);
int				mtx_len(char **mtx);
//data_utils.c
t_data			*data(void);
void			free_cmd_data(void);

#endif
