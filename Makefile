# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 09:14:24 by rfleritt          #+#    #+#              #
#    Updated: 2025/11/12 09:30:18 by rfleritt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED         := \033[91;1m
GREEN       := \033[92;1m
CYAN        := \033[96;1m
YELLOW      := \033[93;1m
CLEAR_COLOR := \033[0m

NAME        := miniRT

CC          := gcc
CFLAGS      := -Wall -Werror -Wextra
RM          := rm -f


SRC_DIR     := src/
OBJ_DIR     := obj/
INCLUDE_DIR := include/

LIBFT_DIR   := libs/libft/
LIBFT       := $(LIBFT_DIR)libft.a

MLX_DIR     := libs/minilibx-linux/
MLX         := $(MLX_DIR)libmlx_Linux.a


SRCS        := $(SRC_DIR)main.c

OBJS        := $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))

HEADERS     := $(INCLUDE_DIR)mini_rt.h


OS = $(shell uname)
ifeq ($(OS), Linux)
	MLX_FLAGS := -L $(MLX_DIR) -lmlx -lXext -lX11 -lm
else
	MLX_FLAGS := -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif


all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(CYAN)✅ Compilado $(NAME) exitosamente!$(CLEAR_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
	@echo "$(GREEN)🔨 Compilando: $<$(CLEAR_COLOR)"

$(LIBFT):
	@echo "$(YELLOW)📚 Compilando libft...$(CLEAR_COLOR)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ libft compilada!$(CLEAR_COLOR)"

$(MLX):
	@echo "$(YELLOW)🖼️  Compilando MiniLibX...$(CLEAR_COLOR)"
	@cd $(MLX_DIR) && ./configure > /dev/null 2>&1 || make -f Makefile.gen
	@echo "$(GREEN)✅ MiniLibX compilada!$(CLEAR_COLOR)"

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