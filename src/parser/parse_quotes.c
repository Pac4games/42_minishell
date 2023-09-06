/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:51:58 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/05 12:09:02 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_inside_quotes(char *str, char c)
{
	int		i;

	i = 0;
	str++;
	data()->warning = 0;
	while (*str && *str != c)
	{
		if (*str == '$' && c == '\"' && str[1] != ' ' && str[1] != '\t'
			&& str[1] != '\n' && str[1] != '\'' && str[1] != '\"' && str[1])
		{
			data()->str_tmp = check_envp(str);
			if (data()->str_tmp)
			{
				data()->warning = -1;
				free(data()->str_tmp);
			}
		}
		str++;
		i++;
	}
	return (i);
}

int	nbr_outside_quotes(char *str)
{
	int	nbr;

	nbr = 0;
	str++;
	while (*str && *str != ' ' && *str != '\n' 
		&& *str != '\t' && *str != '|' && *str != '<' 
		&& *str != '>' && *str != '\'' && *str != '\"')
	{
		str++;
		nbr++;
	}
	return (nbr);
}

char	*handle_quote(char	*str, char c)
{
	str++;
	while (*str && *str != c)
		str++;
	str++;
	return (str);
}

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (0);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

char	*check_envp(char	*str)
{
	int		i;
	char	*tmp;
	char	*output;

	i = 0;
	str++;
	tmp = NULL;
	while (*str && *str != ' ' && *str != '\n' && *str != '\t' && *str != '\"')
	{
		tmp = strjoin_var(tmp, *str);
		i++;
		str++;
	}
	tmp[i] = '\0';
	output = my_getenv(tmp);
	free(tmp);
	tmp = NULL;
	return (output);
}
