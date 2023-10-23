/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_soup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:10:52 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/23 10:10:53 by paugonca         ###   ########.fr       */
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
