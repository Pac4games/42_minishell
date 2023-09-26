/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:06:42 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/26 08:36:30 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	parse_tilde_utils(char *arg, int *i)//duvida
{
	if (arg[*i] && !is_diff_sign("\"'", arg[*i])) // quando usa "'?
		*i = quotes_skip(arg, *i);
	if (*syntax())
	{
		free(arg);
		return (true);
	}
	return (false);
}

static void	gvt_utils(char *arg, int i, char *home, char **res) //ok
{
	int	j;
	int	k;
	int	l;

	j = 0;
	k = 0;
	l = 0;
	while (arg[j + l])
	{
		if ((j + k) == i)
		{
			while (home[k])
			{
				(*res)[j + k] = home[k];
				k++;
			}
			l = 2;
		}
		else
		{
			(*res)[j + k] = arg[j + l];
			j++;
		}
	}
	(*res)[j + k] = 0;
}

static char	*get_var_tilde(char *arg, int i, char *home) //?
{
	char	*res;

	res = malloc(ft_strlen(arg) - 1 + 1 + ft_strlen(home) * sizeof(char)); // -1 + 1 ?
	gvt_utils(arg, i, home, &res);
	free(home);
	return (res);
}

char	*parse_tilde(char *arg, char **env) // ?
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg[i])
	{
		if (parse_tilde_utils(arg, &i)) //ok, com comentarios
			return (NULL);
		if (arg[i] == '~' \
		&& (i == 0 || arg[i - 1] == ' ' || arg[i - 1] == '\t') \
		&& (!arg[i + 1] || arg[i + 1] == ' ' || arg[i + 1] == '\t'))
		{
			tmp = get_var_tilde(arg, i, parse_signs(ft_strdup("$HOME"), env));
			free(arg);
			arg = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (arg);
}
