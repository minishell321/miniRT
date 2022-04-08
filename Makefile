# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburri <rburri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 08:04:22 by rburri            #+#    #+#              #
#    Updated: 2022/04/08 13:59:23 by rburri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################################################
# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
####################################################################
CC = gcc 

NAME = miniRT

FLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L. -lft

MLX_DIR		= minilibx
MLX_A		= libmlx.a
MLX			= -L. -lmlx -framework OpenGL -framework AppKit

SRC = src

BIN = bin

$(shell mkdir -p $(BIN))

SOURCE =  	$(SRC)/main.c\
			$(SRC)/mlx_utils.c\
			$(SRC)/utils.c

					
		
OBJS = $(patsubst %,$(BIN)/%,$(notdir $(SOURCE:.c=.o)))

$(BIN)/%.o : $(SRC)/%.c
				$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

${NAME}:	${OBJS}
			@make -C ${LIBFT_DIR}/
			@cp ${LIBFT_DIR}/$(LIBFT_A) .
			@make -C ${MLX_DIR}/
			@cp ${MLX_DIR}/$(MLX_A) .
			$(CC)  ${OBJS} $(LIBFT) $(MLX) -o $(NAME)
			@echo "$(GREEN)$(NAME) sucessfully created$(RESET)"

clean:
		@rm -f $(OBJS)
		make -C ${LIBFT_DIR} fclean
		make -C ${MLX_DIR} clean

fclean: clean
		@rm -f $(NAME)
		@rm -f $(MLX_A)
		@rm -f $(LIBFT_A)
	
re: fclean all

.PHONY: fclean re all clean bonus
