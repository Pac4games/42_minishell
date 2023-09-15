/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:51:58 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/15 12:15:36 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_skip(char *str, int i)
{
	char	tmp;

	tmp = str[i];
	i++;
	while (str[i] && str[i] != tmp)
		i++;
	if (!str[i])
	{
		ft_putendl_fd("Unclosed quotes!", STDOUT_FILENO);
		print_syntax_error();
	}
	return (i);
}

int	get_quote_num(char *str)
{
	int		i;
	int		num;
	char	tmp;

	i = -1;
	num = 0;
	while (str[++i])
	{
		if (str[i] && !is_diff_sign("\"'", str[i]))
		{
			tmp = str[i++];
			while (str[i] && str[i] != tmp)
				i++;
			num += 2;
		}
	}
	return (num);
}

static char	*quotes_rm_fr(char *str, int i, int j, char tmp)
{
	char	*res;

	res = malloc(ft_strlen(str) - get_quote_num(str) + 1 * sizeof(char));
	while (str[++i])
	{
		if (!is_diff_sign("\"'", str[i]))
		{
			tmp = str[i++];
			while (str[i] && str[i] != tmp)
				res[j++] = str[i++];
		}
		else
			res[j++] = res[i];
	}
	res[j] = 0;
	return (res);
}

char	*quotes_rm(char *str)
{
	char	*res;

	res = quotes_rm_fr(str, -1, 0, ' ');
	printf("quotes_rm() str: %s\n", str);
	printf("quotes_rm() res: %s\n", res);
	free(str);
	return (res);
}
