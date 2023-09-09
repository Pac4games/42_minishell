# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 11:20:48 by paugonca          #+#    #+#              #
#    Updated: 2023/09/09 11:23:28 by paugonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

RM          = rm -f
MKD         = mkdir -p

SRC_PATH    = ./src
OBJ_PATH    = ./obj

SRC_NAME    = main.c						\
              env_utils.c					\
              extra/free_utils.c			\
			  extra/print_utils.c			\
			  extra/data_utils.c			\
#			  parser/parse_init.c			\
#			  parser/parse_quotes.c			\
#			  parser/parse_utils.c			\
#			  parser/utils.c				\
#			  parser/utils2.c				\
#			  parser/utils3.c				\
#			  parser/utils4.c				\
#			  parser/utils5.c				\
              executor/executor.c			\
			  executor/cmd_utils.c			\
              executor/path_utils.c			\
			  executor/sig_utils.c			\
			  executor/redir_utils.c		\
			  executor/redir_in_utils.c		\
			  executor/redir_out_utils.c	\
			  executor/heredoc_utils.c

SRC         = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ         = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))
DEPS        = ./libft/libft.a -lreadline

LIBFT_PATH  = ./libft

all: $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(MKD) -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(DEPS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(DEPS) -o $(NAME)

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
