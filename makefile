# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abuet <abuet@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/16 21:53:05 by antoinebuet       #+#    #+#              #
#    Updated: 2026/04/09 14:26:39 by abuet            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = fdf
CFLAGS  = -Wall -Wextra -Werror -g
CC      = cc
ARGS ?= test_maps/42.fdf
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
################################################################################
## OS DETECTION

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	MLX_PATH = ./minilibx_macos
	MLX_FLAGS = -L$(MLX_PATH) -lmlx \
                -framework OpenGL \
                -framework AppKit
else
	MLX_PATH = ./minilibx-linux
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
endif
################################################################################
## SOURCES

HEADER		= fdf.h linked_list.h struct.h
INCLUDES	= -I$(MLX_PATH) -I. -I$(LIBFT_DIR)

SRC_FILES	= main.c parse.c linked_list.c min_max.c utils.c free_parse.c manage_window.c utils_draw.c\

OBJ_FILES	= $(SRC_FILES:.c=.o)

################################################################################
## RULES
all: libft mlx $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

## Compilation de la mlx selon l'OS
mlx:
ifeq ($(UNAME), Darwin)
	@echo "Compiling MinilibX for macOS..."
	@make -C $(MLX_PATH) 2>/dev/null
else
	@echo "Compiling MinilibX for Linux..."
	@make -C $(MLX_PATH) 2>/dev/null
endif

$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "✓ $(NAME) compiled successfully"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)
	@echo "✓ Objects cleaned"
	@make -C $(LIBFT_DIR) clean 2>/dev/null || true

fclean: clean
	@rm -f $(NAME)
	@make -C $(MLX_PATH) clean 2>/dev/null || true
	@echo "✓ $(NAME) cleaned"
	@make -C $(LIBFT_DIR) fclean 2>/dev/null || true

re: fclean all

launch: all
	@./$(NAME) $(ARGS)
	@make fclean

.PHONY: all clean fclean launch re mlx libft