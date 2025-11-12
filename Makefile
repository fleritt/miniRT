# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 08:47:22 by rfleritt          #+#    #+#              #
#    Updated: 2025/11/12 08:51:48 by rfleritt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx_Linux.a

CC = gcc
CFLAGS 	= -Wall -Werror -Wextra
MINILIBX_FLAGS	= -L mlx/ -lmlx -lXext -lX11
RM = rm -f

SRC = ./src/main.c
OBJ = $(SRC:.c=.o)
	
all: ${MLX} ${LIBFT} ${NAME}

${NAME}: ${OBJ}
		${CC} ${SRC} ${MLX} ${LIBFT} ${CFLAGS} ${MINILIBX_FLAGS} -o ${NAME}

${LIBFT}:
		make -C libft/

bonus: ${OBJ}
		${CC} ${SRC} ${MLX} ${LIBFT} ${CFLAGS} ${MINILIBX_FLAGS} -o ${NAME}

clean: 
		make clean -C libft/
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}
		make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re