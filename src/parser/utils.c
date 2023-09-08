/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:06:25 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/08 11:28:52 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_here(char *s1, char *s2)
{
	char	*s_final;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen(s1) + ft_strlen(s2);
	s_final = (char *)malloc(size + 2);
	if (!s_final)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		s_final[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < size)
		s_final[i++] = s2[j++];
	s_final[i++] = '\n';
	s_final[i] = '\0';
	free(s1);
	free(s2);
	return (s_final);
}

void	handle_error_var(void)
{
	char	*str;
	char	*nbr;

	nbr = ft_itoa(data()->error);
	str = ft_strjoin("?=", nbr);
	add_cd_to_env(str);
	free(nbr);
	free(str);
}

char	*strjoin_var(char *s1, char s2)
{
	char	*s_final;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1) + 1;
	s_final = (char *)malloc(size + 1);
	if (!s_final)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		s_final[i] = s1[i];
		i++;
	}
	while (i < size)
		s_final[i++] = s2;
	s_final[i] = '\0';
	free(s1);
	s1 = NULL;
	return (s_final);
}

char	*strjoin_null(char *s1, char *s2)
{
	char	*s_final;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen(s1) + ft_strlen(s2);
	s_final = (char *)malloc(size + 1);
	if (!s_final)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		s_final[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < size)
		s_final[i++] = s2[j++];
	s_final[i] = '\0';
	if (s2 != NULL)
		free(s2);
	if (s1 != NULL)
		free(s1);
	return (s_final);
}

char	*env_var(char *str)
{
	char	*result;

	result = NULL;
	str++;
	while (*str && *str != '\"')
	{
		if (*str == '$')
		{
			str++;
			handle_env(str);
			if (data()->str_tmp != NULL)
			{
				result = strjoin_null(result, data()->str_tmp);
				skip_non_whitespace_and_dolar_sign(&str);
			}
			else
				skip_non_whitespace_and_dolar_sign(&str);
		}
		else
		{
			result = strjoin_var(result, *str);
			str++;
		}
	}
	return (result);
}
