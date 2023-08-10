/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:02:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/08/10 11:19:56 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//My own libft
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

//Binary Tree struct
typedef struct s_node
{
	int				data;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
}			t_node;

#endif
