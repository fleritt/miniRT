# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 09:14:24 by rfleritt          #+#    #+#              #
#    Updated: 2026/01/29 19:32:46 by ricardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED         := \033[91;1m
GREEN       := \033[92;1m
CYAN        := \033[96;1m
YELLOW      := \033[93;1m
CLEAR_COLOR := \033[0m

NAME        := miniRT

CC          := gcc
CFLAGS      := -Wall -Werror -Wextra -g3
RM          := rm -f

SRC_DIR     := src/
OBJ_DIR     := obj/
INCLUDE_DIR := include/

LIBFT_DIR   := libs/libft/
LIBFT       := $(LIBFT_DIR)libft.a

MLX42_DIR     := libs/mlx
MLX         := $(MLX42_DIR)/build/libmlx42.a


SRCS        := main.c \
				window/init_window.c \
				window/ft_render.c \
				window/key_register.c \
				math/vec_add.c \
				math/vec_dot.c \
				math/vec_length.c \
				math/vec_multiply.c \
				math/vec_new.c \
				math/vec_norm.c \
				math/vec_sub.c \
				math/vec_cross.c \
				parser/ft_error.c \
				parser/init_scene.c \
				parser/parse_data.c \
				parser/parse_elements.c \
				parser/parse_scene.c \
				parser/set_elements.c \
				ray_tracer/hit_sphere.c \
				ray_tracer/camera.c \

OBJS        := $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

HEADERS     := $(INCLUDE_DIR)minirt.h $(INCLUDE_DIR)data_minirt.h


OS = $(shell uname)
ifeq ($(OS), Linux)
	MLX_FLAGS := -ldl -lglfw -pthread -lm
else
	MLX_FLAGS := -L $(MLX42_DIR) -lmlx -framework OpenGL -framework AppKit
endif


all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(CYAN)✅ Compilado $(NAME) exitosamente!$(CLEAR_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
	@echo "$(GREEN)🔨 Compilando: $<$(CLEAR_COLOR)"

$(LIBFT):
	@echo "$(YELLOW)📚 Compilando libft...$(CLEAR_COLOR)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ libft compilada!$(CLEAR_COLOR)"

$(MLX):
	@cmake -B $(MLX42_DIR)/build $(MLX42_DIR)
	@cmake --build $(MLX42_DIR)/build
	@echo "$(GREEN)✅ Compilado MLX42\n$(CLEAR_COLOR)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(RED)🧹 Objetos eliminados$(CLEAR_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(RED)🗑️  Ejecutable eliminado$(CLEAR_COLOR)"

re: fclean all


run: all
	@echo "$(CYAN)🚀 Ejecutando $(NAME)...$(CLEAR_COLOR)"
	@./$(NAME)

norminette:
	@echo "$(YELLOW)📝 Ejecutando norminette...$(CLEAR_COLOR)"
	@norminette $(SRCS) $(HEADERS) $(LIBFT_DIR)

valgrind: all
	@echo "$(CYAN)🔍 Ejecutando valgrind...$(CLEAR_COLOR)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

debug: CFLAGS += -g3 -fsanitize=address
debug: re
	@echo "$(YELLOW)🐛 Compilado en modo DEBUG$(CLEAR_COLOR)"

.PHONY: all clean fclean re run norminette valgrind debug