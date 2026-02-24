# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/16 21:53:05 by antoinebuet       #+#    #+#              #
#    Updated: 2026/02/24 14:07:26 by antoinebuet      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = fdf
CFLAGS  = -Wall -Wextra -Werror -g
CC      = cc
ARGS ?= 

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

HEADER		= fdf.h
INCLUDES	= -I$(MLX_PATH) -I.

SRC_FILES	= main.c \

OBJ_FILES	= $(SRC_FILES:.c=.o)

################################################################################
## RULES

all: mlx $(NAME)

## Compilation de la mlx selon l'OS
mlx:
ifeq ($(UNAME), Darwin)
	@echo "Compiling MinilibX for macOS..."
	@make -C $(MLX_PATH)
else
	@echo "Compiling MinilibX for Linux..."
	@make -C $(MLX_PATH)
endif

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(MLX_FLAGS) -o $(NAME)
	@echo "✓ $(NAME) compiled successfully"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)
	@echo "✓ Objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@make -C $(MLX_PATH) clean 2>/dev/null || true
	@echo "✓ $(NAME) cleaned"

re: fclean all

launch: all
	@./$(NAME) $(ARGS)
	@make fclean

.PHONY: all clean fclean launch re mlx