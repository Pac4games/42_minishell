/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:15:56 by psoares-          #+#    #+#             */
/*   Updated: 2023/10/21 20:21:52 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*is_inside(void)
{
	static int	i;

	return (&i);
}

struct termios	*term(void)
{
	static struct termios	t;

	return (&t);
}
