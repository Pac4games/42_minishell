/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:59:05 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/29 11:31:55 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	parse_str_redir(char *str, t_parse parse, int *i) // 2ok
{
	printf("entrou em parse_str_redir e str eh %s\n", str);
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

static void	parse_str(char *str, t_parse parse, bool exp) // 2 ok com comentarios e duvidas
{
	printf("entrou em parse_str\n");
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
			i++; // se nao incrementar i aqui supondo nao ter " " ou /t, onde incrementa?
		if (parse_str_redir(str, parse, &i))
			; // eh isso mesmo? parece faltar algo aqui..
		else if (str[i] && str[i] == '-' && str[i + 1] && str[i + 1]
			&& is_diff_sign("<>|&", str[i + 1]) && cmd) // repete str[i + 1] nessa chamada
			i = tree_add_case(str, i - 1, E_FLAG, parse);
		else if (str[i] && cmd != 0)
		{
			printf("opcao str[i] && cmd != 0\n");
			i = tree_add_case(str, i - 1, E_ARG, parse);
		}
		else if (str[i])
		{
			printf("opcao so str[i] sendo str[i] %c\n", str[i]);
			i = tree_add_case(str, i - 1, E_CMD, parse);
			cmd++;
		}
	}
	printf("saiu da funcao parse_str\n");
}

static void	parse_pipes(char *arg, char **mtx, t_tree **root, char **env) //2 ok, mas seria bom uma explicacao rs
{
	printf("entrou em parse_pipe\n");
	t_parse	parse;

	parse.pos = 0;
	parse.env = env;
	parse.tree = root;
	if (!mtx)
	{
		printf("1\n\n");
		parse_str(arg, parse, false);
		printf("parse_pipes acabou aqui\n");
	}
	else
	{
		printf("se nao acabou entra\n");
		while (mtx[parse.pos])
		{
			printf("2\n\n");
			parse_str(mtx[parse.pos++], parse, false);
		}
	}
	free_mtx(mtx);
	printf("saiu de parse_pipes\n");
}

//Our partner in crime and best-friend: the parser
void	parsa(char *in, char ***env, t_tree **root, int num) //2
{
	printf("entrou em parsa\n");
	char	**mtx; // qual a definicao dessa sigla?
	t_pipe	*pipes;

	pipes = NULL;
	in = parse_tilde(in, *env);
	check_pipes(in);
	if (!in)
		return ;
	parse_all(root, in, &pipes, num);
	if (*syntax())
		return ;
	mtx = pipe_split(pipes, in); // ate aqui, pipes ainda eh NULL ou quando assume a struct muda?
	parse_pipes(in, mtx, root, *env);
	free_pipes(&pipes);
	free(in);
	if (!(*syntax()))
		proc_exec_tree(root, env);
}
