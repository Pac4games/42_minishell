# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 11:20:48 by paugonca          #+#    #+#              #
#    Updated: 2023/08/10 12:56:36 by paugonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

RM			= rm -f
MKD			= mkdir

SRC_NAME	= main.c		\
			  extra_utils.c	\
			  env_utils.c

SRC			= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ			= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))
DEPS		= ./libft/libft.a

SRC_PATH	= ./src
OBJ_PATH	= ./obj

all: $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(DEPS) $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(DEPS) -o $(NAME)

LIBFT_PATH	= ./libft
./libft/libft.a: $(shell make -C $(LIBFT_PATH) -q libft.a)
	make bonus -C $(LIBFT_PATH)

$(OBJ_PATH):
	$(MKD) -p obj

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
