/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:23:12 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/08 11:29:04 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_dollar_sign(char *str)
{
	int	i;

	i = 0;
	str++;
	handle_env(str);
	while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t'
		&& str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '$'
		&& str[i] != '\'' && str[i] != '\"' && str[i] != '/')
	{
		i++;
		if (str[i - 1] == '?')
			break ;
	}
	if (!data()->str_tmp)
		data()->warning = -1;
	return (i);
}

int	check_special_char(int i)
{
	if (data()->tokens[i])
	{
		if (ft_strncmp(data()->tokens[i], ">", 2) == 0
			|| ft_strncmp(data()->tokens[i], "<", 2) == 0
			|| ft_strncmp(data()->tokens[i], "\'", 2) == 0
			|| ft_strncmp(data()->tokens[i], "\"", 2) == 0
			|| ft_strncmp(data()->tokens[i], ">>", 3) == 0
			|| ft_strncmp(data()->tokens[i], "<<", 3) == 0
			|| ft_strncmp(data()->tokens[i], "./", 2) == 0)
			return (1);
		else
			return (0);
	}
	return (-1);
}

void	verify_echo_spaces(int i)
{
	while (data()->tokens[++i] != NULL && data()->tokens[i + 1] != NULL
		&& ft_strncmp(data()->tokens[i], "|", 2) != 0)
		if (check_special_char(i) == 0)
			if ((check_special_char(i + 1) == 1
					&& data()->tokens[i + 3] != NULL
					&& check_special_char(i + 3) == 0
					&& ft_strncmp(data()->tokens[i + 3], "|", 2) != 0)
				|| (check_special_char(i + 1) == 0
					&& ft_strncmp(data()->tokens[i + 1], "|", 2) != 0))
				(data()->tokens[i])
					= strjoin_var(data()->tokens[i], ' ');
}

void	check_echo(void)
{
	int	i;

	i = 0;
	while (data()->tokens[i] != NULL)
	{
		if ((ft_strncmp(data()->tokens[i], "echo", 5) == 0)
			&& data()->tokens[i + 1] != NULL)
		{
			if (ft_strncmp(data()->tokens[i + 1], "-n", 2) == 0)
				i += 1;
			verify_echo_spaces(i);
		}
		i++;
	}
}

void	handle_shlvl(char c)
{
	int		shlvl;
	char	*str;
	char	*nbr;
	char	*env;

	env = my_getenv("SHLVL");
	shlvl = ft_atoi(env);
	if (c == '-')
		shlvl--;
	else if (c == '+')
		shlvl++;
	nbr = ft_itoa(shlvl);
	str = ft_strjoin("SHLVL=", nbr);
	ft_unset(data()->env_p, "SHLVL");
	add_cd_to_env(str);
	free(nbr);
	free(str);
	free(env);
}
