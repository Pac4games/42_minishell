/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:45:57 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/08 11:28:46 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function to count the tokens
int	count_tokens(char *str)
{
	int	i;

	i = 0;
	str += skip_whitespace(str);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (str[1] != *str)
			{
				str = handle_quote(str, *str);
				i++;
				if (*str == '\0')
					return (i);
			}
			else
				str += 2;
		}
		else
			handle_special_characters(&str, &i);
		str += skip_whitespace(str);
	}
	return (i);
}

char	**alloc_tokens(char *str, int nbr_tokens)
{
	int		i;
	char	**tokens;

	i = 0;
	tokens = init_tokens(nbr_tokens);
	str += skip_whitespace(str);
	while (*str)
	{
		data()->warning = 0;
		if (*str == '\'' || *str == '\"')
			str += token_inside_quote(str, &tokens[i]);
		else if ((*str == '|' || *str == '>' || *str == '<'))
			str += token_special_char(str, &tokens[i], &i);
		else if (*str == '$' && str[1] != ' ' && str[1] != '\t'
			&& str[1] != '\n' && str[1])
			str += token_space_dolar_sig(str, &tokens[i], nbr_tokens);
		else if (*str && (*str == ' ' || *str == '\n' || *str == '\t'))
			str += token_is_space(str, &i);
		else
			str += token_other_chars(str, &tokens[i], &i);
		nbr_tokens--;
	}
	return (tokens);
}

// Function to generate tokens from the str_cmd.
int	get_tokens(void)
{
	int	i;

	i = 0;
	while (data()->str_cmd[i] && (data()->str_cmd[i] == ' '
			|| data()->str_cmd[i] == '\n' || data()->str_cmd[i] == '\t'))
		i++;
	if (data()->str_cmd[i] == '\0')
		return (0);
	if (check_quotes(data()->str_cmd) == 0)
	{
		perror("Error unclosed quotes");
		return (0);
	}
	(data()->nbr_tokens) = count_tokens(data()->str_cmd);
	(data()->tokens) = alloc_tokens(data()->str_cmd, data()->nbr_tokens);
	check_echo();
	ft_unset(data()->env_p, "?");
	return (1);
}
