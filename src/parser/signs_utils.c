/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:48:21 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/09 17:20:28 by paugonca         ###   ########.fr       */
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
		if (str[i] && !is_diff_sign("\"", str[i]))
			dol_sign_util(&tmp);
		if (str[i] && !is_diff_sign("'", str[i]) && !tmp)
			i = skip_quotes(str, i);
		if (*syntax())
			return (free_str_ret_null(str));
		if (str[i] && !is_diff_sign("$", str[i]))
			str = get_var(str, &i, env);
		else
			i++;
	}
	return (str);
}
