/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:59:05 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/26 10:12:09 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	parse_str_redir(char *str, t_parse parse, int *i) //?
{
	int	j;

	j = *i;
	if (str[j] && str[j] == '>' && str[j + 1] != '>')
		*i = tree_add_case(str, j, E_STDOUT, parse);
	else if (str[j] && str[j] == '<' && str[j + 1]
		&& str[j + 1] != '<')
		*i = tree_add_case(str, j, E_STDIN, parse);
	else if (str[j] && str[j] == '>' && str[j + 1]
		&& str[j + 1] == '>' && str[j + 2] != '>')
		*i = tree_add_case(str, j, E_APPEND, parse);
	else if (str[j] && str[j] == '<' && str[j + 1]
		&& str[j + 1] == '<' && str[j + 2] != '<')
		*i = tree_add_case(str, j, E_HDOC, parse);
	else
		return (false);
	return (true);
}

static void	parse_str(char *str, t_parse parse, bool exp) //ok com comentarios
{
	int	i;
	int	cmd;

	cmd = 0;
	i = 0;
	parse.exp = &exp;
	while (str[i])
	{
		if (*syntax())
			return ;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (parse_str_redir(str, parse, &i))
			; // eh isso mesmo?
		else if (str[i] && str[i] == '-' && str[i + 1] && str[i + 1]
			&& is_diff_sign("<>|&", str[i + 1]) && cmd)
			i = tree_add_case(str, i - 1, E_FLAG, parse);
		else if (str[i] && cmd != 0)
			i = tree_add_case(str, i - 1, E_ARG, parse);
		else if (str[i])
		{
			i = tree_add_case(str, i - 1, E_CMD, parse);
			cmd++;
		}
	}
}

static void	parse_pipes(char *arg, char **mtx, t_tree **root, char **env) //ok
{
	t_parse	parse;

	parse.pos = 0;
	parse.env = env;
	parse.tree = root;
	if (!mtx)
		parse_str(arg, parse, false);
	else
		while (mtx[parse.pos])
			parse_str(mtx[parse.pos++], parse, false);
	free_mtx(mtx);
}

//Our partner in crime and best-friend: the parser
void	parsa(char *in, char ***env, t_tree **root, int num)
{
	char	**mtx; // definicao?
	t_pipe	*pipes;

	pipes = NULL;
	in = parse_tilde(in, *env);
	check_pipes(in);
	if (!in)
		return ;
	parse_all(root, in, &pipes, num);
	if (*syntax())
		return ;
	mtx = pipe_split(pipes, in);
	parse_pipes(in, mtx, root, *env);
	free_pipes(&pipes);
	free(in);
	if (!(*syntax()))
		proc_exec_tree(root, env);
}
