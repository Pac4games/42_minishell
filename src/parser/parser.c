/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:59:05 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/11 12:22:03 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_str_redir(char *str, t_parse parse, int *i)
{
	int	j;

	j = *i;
	if (str[j] == '>' && str[j + 1] != '>')
		*i = 
}

static void	parse_str(char *str, t_parse parse, int exp)
{
	int		i;
	bool	iscmd;

	i = 0;
	iscmd = false;
	tmp.exp = &exp;
	while (str[i])
	{
		if (*syntax())
			return ;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	}
}

static void	parse_pipes(char *arg, char **mtx, t_tree **root, char **env)
{
	t_parse	parse;

	parse.pos = 0;
	parse.env = env;
	parse.tree = root;
	if (!mtx)
		parse_str();
}

//Our partner in crime and best-friend: the parser
void	parsa(char *in, char ***env, t_tree **root, int num)
{
	int		i;
	char	**mtx;
	t_pipe	*pipes;

	i = 0;
	pipes = NULL;
	in = parse_tilde(in, *env);
	check_pipes(in);
	if (!in)
		return ;
	parse_all(root, in, &pipes, num);
	if (*syntax())
		return ;
	mtx = pipe_split(pipes, in);
	
}
