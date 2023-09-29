/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:51:58 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/29 15:40:27 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_skip(char *str, int i) //2ok
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

int	get_quote_num(char *str)//2-
{
	int		i;
	int		num;
	char	tmp;

	i = -1;
	num = 0;
	while (str[++i])
	{
		if (str[i] && !is_diff_sign("\"'", str[i])) // novamente "'
		{
			tmp = str[i++];
			while (str[i] && str[i] != tmp)
				i++;
			num += 2; //pq +2? Duas aspas abre e fecha?
		}
	}
	return (num);
}

static char	*quotes_rm_fr(char *str, int i, int j, char tmp)// 2 poucas duvidas, mais relacionada a repeticao "'
{
	char	*res;

	res = malloc(ft_strlen(str) - get_quote_num(str) + 1 * sizeof(char));
	while (str[++i])
	{
	//	printf("str[i] %c\n", str[i]);
		if (!is_diff_sign("\"'", str[i])) // novamente "'
		{
			tmp = str[i++];
			while (str[i] && str[i] != tmp)
				res[j++] = str[i++];
		}
		else
		{
		//	printf("str[i] eh %c nao achou aspas\n", str[i]);
			res[j++] = str[i]; // nao sei se eh isso que pretendia, faz mais sentido pra mim que igualar a null
		}
	}
	res[j] = 0;
	return (res);
}

char	*quotes_rm(char *str)// 2 ainda sobre "'
{
	//printf("entrou em quotes_rm\n");
	char	*res;

	res = quotes_rm_fr(str, -1, 0, ' ');
	//printf("quotes_rm() str: %s\n", str);
	//printf("quotes_rm() res: %s\n", res);
	free(str);
	//printf("saiu de quotes_rm\n\n");
	return (res);
}
