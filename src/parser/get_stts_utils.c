/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stts_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:32:50 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/14 16:07:26 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_stts_utils(char *str, int i, char *val, char **res)
{
	int		k;
	int		j;
	int		l;

	l = 0;
	k = 0;
	j = 0;
	while (str[k + l])
	{
		if ((k + j) == i)
		{
			while (val[j])
			{
				(*res)[k + j] = val[j];
				j++;
			}
			l = 2;
		}
		else
		{
			(*res)[k + j] = str[k + l];
			k++;
		}
	}
	(*res)[k + j] = 0;
}

char	*get_stts(char *str, int i, char *val)
{
	char	*res;

	res = malloc(ft_strlen(str) - 2 + ft_strlen(val) + 1);
	get_stts_utils(str, i, val, &res);
	free(val);
	free(str);
	return (res);
}
