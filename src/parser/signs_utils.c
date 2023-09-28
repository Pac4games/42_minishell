/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:48:21 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/28 12:09:44 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_eq_sign(char *str) // 2ok
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

static void	dol_sign_util(int *tmp) //2ok
{
	if (!(*tmp))
		*tmp = 1;
	else
		*tmp = 0;
}

static char	*free_str_ret_null(char *str) // 2ok
{
	free(str);
	return (NULL);
}

char	*parse_signs(char *str, char **env) // 2ok, porem o syntax ainda nao entendi..
{
	printf("entrou parse_sig\n");
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
			return (free_str_ret_null(str));// ainda nao entendi o syntax :/
		if (!is_diff_sign("$", str[i]))
			str = get_var(str, &i, env);
		else
			i++;
	}
	printf("saiu de parse_sig\n");
	return (str);
}

bool	is_diff_sign(char *sign, char c) //2ok
{
	int	j;

	j = 0;
	while (c && sign[j] && c != sign[j])
		j++;
	if (!sign[j])
		return (true);
	return (false);
}
