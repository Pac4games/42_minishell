/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:48:21 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/04 11:34:20 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_eq_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

static void	dol_sign_util(int *tmp)
{
	if (!(*tmp))
		*tmp = 1;
	else
		*tmp = 0;
}

static char	*free_str_ret_null(char *str)
{
	free(str);
	return (NULL);
}

char	*parse_signs(char *str, char **env)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (str[i])
	{
		if (!str[i])
			return (str);
		if (!is_diff_sign("\"", str[i]))
			dol_sign_util(&tmp);
		if (!is_diff_sign("'", str[i]) && !tmp)
			i = quotes_skip(str, i);
		if (*syntax())
			return (free_str_ret_null(str));
		if (!is_diff_sign("$", str[i]))
			str = get_var(str, &i, env);
		else
			i++;
	}
	return (str);
}

bool	is_diff_sign(char *sign, char c)
{
	int	j;

	j = 0;
	while (c && sign[j] && c != sign[j])
		j++;
	if (!sign[j])
		return (true);
	return (false);
}
