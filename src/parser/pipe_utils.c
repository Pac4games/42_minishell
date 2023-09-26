/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:44:19 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/26 08:58:48 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_pipes_utils(char *arg, int *i) //ok
{
	while (arg[*i])
	{
		if (!is_diff_sign("\"'", arg[*i])) // novamente "'
			*i = quotes_skip(arg, *i);
		if (!is_diff_sign("|", arg[*i]))
		{
			(*i)++;
			while ((arg[*i] == ' ' || arg[*i == '\t']))
				(*i)++;
			if (!is_diff_sign("|", arg[*i]))
				print_syntax_error();
		}
		else
			(*i)++;
		if (*syntax())
			return ;
	}
}

void	check_pipes(char *arg) // com comentarios
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	if (!arg[i] || !is_diff_sign("|", arg[i])) // se ele tiver | erro de syntax?
		print_syntax_error();
	parse_pipes_utils(arg, &i);
	if (*syntax())
		return ;
}

void	pipe_add2pos(t_pipe **pipes, int pos, int num) //ok
{
	t_pipe	*res;
	t_pipe	*tmp;

	tmp = *pipes;
	res = malloc(sizeof(*res));
	res->pos = pos;
	res->num = num;
	res->next = NULL;
	if (!tmp)
	{
		*pipes = res;
		return ;
	}
	while (tmp)
		tmp = tmp->next;
	tmp->next = res;
}

char	**pipe_split(t_pipe *pipes, char *arg) // com comentarios
{
	int		i;
	char	**res;
	t_pipe	*tmp;

	if (!pipes)
		return (NULL);
	tmp = pipes;
	while (tmp->next)
		tmp = tmp->next;
	res = malloc((tmp->num * 3) * sizeof(char *)); // pq *3?
	i = 0;
	while (pipes) // nao compreendi
	{
		res[pipes->num] = ft_substr(arg, i, pipes->pos - 1);
		i = pipes->pos + i;
		if (!pipes->next)
		{
			res[pipes->num + 1] = ft_substr(arg, i, ft_strlen(arg) - 1);
			res[pipes->num + 2] = NULL;
		}
		pipes = pipes->next;
	}
	return (res);
}

void	free_pipes(t_pipe **pipes) //ok
{
	if (!pipes || !(*pipes))
		return ;
	free_pipes(&((*pipes)->next));
	free(*pipes);
	*pipes = NULL;
}
