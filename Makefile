# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 13:56:52 by esnowpea          #+#    #+#              #
#    Updated: 2020/07/27 16:25:59 by esnowpea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fdf

CC = gcc
FLAGS = -Wall -Werror -Wextra -O2
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEADERS) -I$(LIBMLX_HEADERS)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HEADERS = $(LIBFT_DIR)inc/

LIBMLX = $(LIBMLX_DIR)libmlx.a
LIBMLX_DIR = ./minilibx_macos/
LIBMLX_HEADERS = $(LIBMLX_DIR)

HEADERS_LIST = fdf.h
HEADERS_DIR = ./inc/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_DIR = src/
SRC_LIST =	main.c read_map.c ft_atoi_base.c hook.c mlx_put_line.c projection.c event_handler.c print_image.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GRN = \033[0;32m
RED = \033[0;31m
YEL = \033[1;33m
END = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(LIBFT_FLAGS) $(INCLUDES) $(OBJ) -o $@
	@echo "\n$(NAME): $(GRN)*.o files created$(END)"
	@echo "$(NAME): $(GRN)$(NAME) created$(END)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME): $(GRN)$(OBJ_DIR) created$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GRN).$(END)\c"

$(LIBFT):
	@echo "$(NAME): $(GRN)Creating $(LIBFT)...$(END)"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) deleted$(END)"
	@echo "$(NAME): $(RED)*.o files deleted$(END)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) deleted$(END)"

re: fclean all
