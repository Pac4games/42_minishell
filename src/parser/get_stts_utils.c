/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stts_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:32:50 by paugonca          #+#    #+#             */
/*   Updated: 2023/09/09 16:40:38 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_stts_utils(char *str, int i, char *val, char **res)
{
	int	j;
	int	k;
	int	l;

	j = 0;
	k = 0;
	l = 0;
	while (str[j + l])
	{
		if ((j + k) == i)
		{
			while (val[k])
			{
				(*res)[j + k] = val[k];
				k++;
			}
			l = 2;
		}
		else
		{
			(*res)[j + k] = str[j + l];
			j++;
		}
	}
	(*res)[j + k] = 0;
}

char	*get_stts(char *str, int i, char *val)
{
	char	*res;

	res = malloc(ft_strlen(str) - 2 * ft_strlen(val) + 1);
	get_stts_utils(str, i, val, &res);
	free(val);
	free(str);
	return (res);
}
