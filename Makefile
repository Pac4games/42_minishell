# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 11:20:48 by paugonca          #+#    #+#              #
#    Updated: 2023/08/17 11:11:57 by paugonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

RM          = rm -f
MKD         = mkdir -p

SRC_PATH    = ./src
OBJ_PATH    = ./obj

SRC_NAME    = main.c				\
              extra_utils.c			\
              executor/xqt.c		\
              executor/path_utils.c	\
              executor/env_utils.c

SRC         = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ         = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))
DEPS        = ./libft/libft.a

LIBFT_PATH  = ./libft

all: $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(MKD) -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(DEPS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(DEPS) -o $(NAME)

$(LIBFT_PATH)/libft.a:
	make bonus -C $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
