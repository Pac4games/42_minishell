/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:48:10 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/05 12:09:38 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_spc_quote(char *str)
{
	char	*spc;

	spc = ft_substr("\"", 0, 2);
	if ((str[1] == '>' || str[1] == '<') && (str[2] == str[1]))
	{
		spc = strjoin_var(spc, str[1]);
		return (strjoin_var(spc, str[2]));
	}
	else
		return (strjoin_var(spc, str[1]));
}

int	token_is_space(char *str, int *i)
{
	int	j;

	j = skip_whitespace(str);
	(*i)++;
	return (j);
}
