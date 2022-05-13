# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburri <rburri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 08:04:22 by rburri            #+#    #+#              #
#    Updated: 2022/05/13 14:19:27 by rburri           ###   ########.fr        #
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

FLAGS = -Wall -Wextra -Werror -g3

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
			$(SRC)/utils.c\
			$(SRC)/utils2.c\
			$(SRC)/parsing_utils.c\
			$(SRC)/parsing.c\
			$(SRC)/upload_scene.c\
			$(SRC)/ft_atof.c\
			$(SRC)/create_shape.c\
			$(SRC)/scene_utils.c\
			$(SRC)/vector_utils.c\
			$(SRC)/vector_utils2.c\
			$(SRC)/tracing.c\
			$(SRC)/ray_utils.c\
			$(SRC)/upload_scene_utils.c\
			$(SRC)/shapes_inter.c\
			$(SRC)/sc_inter.c\
			$(SRC)/shapes_inter_cn.c\
			$(SRC)/shapes_inter_cy.c\
			$(SRC)/shapes_inter_cy_open.c\
			
		
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

fclean: clean
		@rm -f $(NAME)
		@rm -f $(MLX_A)
		@rm -f $(LIBFT_A)
		make -C ${LIBFT_DIR} fclean
		make -C ${MLX_DIR} clean		
	
re: fclean all

.PHONY: fclean re all clean bonus
