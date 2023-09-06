/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:41:20 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/06 15:03:00 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_declare_exec(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i] != NULL)
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (str[i][j] != '=')
			write(1, &str[i][j++], 1);
		write(1, &str[i][j++], 1);
		write(1, "\"", 1);
		while (str[i][j] != '\0')
			write(1, &str[i][j++], 1);
		write(1, "\"\n", 2);
		i++;
	}
	data()->error = 0;
}

void	export_declare(void)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
			exit_child();
		dup2(data()->fd[0][1], STDOUT_FILENO);
		export_declare_exec(data()->env_p);
		swap_fd();
		swap_fd();
		free_all();
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status > 0)
			data()->error = status / 256;
		else
			data()->error = 0;
	}
}

void	check_env_name(char **env, char *str, int size)
{
	int	i;

	i = 0;
	while (env && env[i] != NULL)
	{
		if (!ft_strncmp(env[i], str, size) && env[i][size] == '=')
		{
			unset_var(env, i);
			return ;
		}
		i++;
	}
}

int	check_export(char **str, int i, int j)
{
	while (str && str[j] != NULL)
	{
		i = 0;
		while (str[j] && str[j][i] != '\0')
		{
			if ((i == 0 && (str[j][i] == '=' \
			|| ft_isdigit(str[j][i]))) || str[j][i] == '-')
			{
				error_msg("export: `", str[j], \
				"': not a valid identifier", 1);
				return (0);
			}
			else if (str[j][i] == '=')
			{
				check_env_name(data()->env_p, str[j], i);
				return (j);
			}
			i++;
		}
		j++;
	}
	return (0);
}

void	ft_export(void)
{
	int		j;
	int		new;
	char	**new_str;

	if (data()->cmds[data()->curr_cmd][1] == NULL)
		export_declare();
	new = check_export(data()->cmds[data()->curr_cmd], 0, 0);
	if (new < 1 || data()->fd[0][0] != STDIN_FILENO \
	|| data()->fd[0][1] != STDOUT_FILENO)
		return ;
	j = 0;
	while (data()->env_p && data()->env_p[j] != NULL)
		j++;
	new_str = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (data()->env_p && data()->env_p[j] != NULL)
	{
		new_str[j] = ft_strdup(data()->env_p[j]);
		j++;
	}
	new_str[j++] = ft_strdup(data()->cmds[data()->curr_cmd][new]);
	new_str[j] = NULL;
	free_double_ptr(data()->env_p);
	data()->env_p = new_str;
	data()->error = 0;
}
