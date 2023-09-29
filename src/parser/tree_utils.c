/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:31:49 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/29 11:24:32 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tree_add_pipe(t_tree **root) //2 ok
{
	t_tree	*tmp;
	t_tree	*pipe;

	tmp = *root;
	pipe = malloc(sizeof(*pipe));
	pipe->type = E_PIPE;
	pipe->left = NULL;
	pipe->right = NULL;
	pipe->parent = NULL;
	pipe->content = NULL;
	if (!tmp)
	{
		*root = pipe;
		return ;
	}
	while (tmp->parent)
		tmp = tmp->parent;
	tmp = tmp->parent;
	pipe->left = tmp;
}

static void	tar_util(char *arg, int *i, int *j) // 2?
{
	while (arg[*i] && (arg[*i] == ' ' || arg[*i] == '\t'))
		(*i)++;
	if (!arg[*i])
		print_syntax_error();
	*j = *i;
	while (arg[*j] && (arg[*j] == ' ' || arg[*j] == '\t'))
		(*j)++;
}

static void	tar_util2(char *arg, t_ndtype type, t_parse parse) // 2ok
{
	printf("entrou tar_util2 com arg %s type %d e parse.tree %p\n", arg, type, parse.tree);
	if (type == E_HDOC)
	{
		if (!(*(parse.tree)))
		{
			printf("opcao 1\n");
			tree_add_n_parse(parse.tree, quotes_rm(arg), type);
		}
		else
		{
			printf("opcao 2\n");
			tree_add_node(quotes_rm(arg), type, parse);
		}
	}
	else
	{
		if (!(parse.tree))
		{
			printf("opcao 3\n");
			tree_add_n_parse(parse.tree, \
			quotes_rm(parse_signs(arg, parse.env)), type);
		}
		else
		{
			printf("opcao 4\n");
			tree_add_node(quotes_rm(parse_signs(arg, parse.env)), type, parse);
		}
	}
	printf("saiu de tar_util2\n\n");
}

static void	check_export(char *arg, t_ndtype type, t_parse parse) // 2?
{
	printf("entrou check_export com arg %s\n", arg);
	char	*tmp;

	printf("check_export() arg: %s\n", arg);
	tmp = quotes_rm(arg);
	if (!ft_strncmp(tmp, "export", ft_strlen(tmp)) && type == E_CMD)
		*(parse.exp) = true;
	free(tmp);
	printf("saiu de check_export\n\n");
}

int	tree_add_case(char *arg, int i, t_ndtype type, t_parse parse) // 2?
{
	printf("entrou em tree_add_case\n\n");
	int	j; // Onde esta inicializado? Podemos usar sem inicializar pela norminette?

	if (type == E_HDOC || type == E_APPEND)
		i++;
	i++;
	tar_util(arg, &i, &j);
	if (!(arg[j] || is_diff_sign("<>|&", arg[j]))) // aqui nao entra /t mesmo?
		print_syntax_error();
	while (arg[j] && is_diff_sign("<>|& \t", arg[j])) // aqui temos um " " antes de /t. Intencional?
	{
		if (!is_diff_sign("\"'", arg[j])) // novamente "'
			j = quotes_skip(arg, j);
		j++;
	}
	if (*syntax())
		return (0);
	check_export(ft_substr(arg, i, j - 1), type, parse);
	tar_util2(ft_substr(arg, i, j - 1), type, parse);
	printf("saiu de tree_add_case\n");
	return (j);
}
