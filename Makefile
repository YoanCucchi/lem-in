# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 15:15:52 by ycucchi           #+#    #+#              #
#    Updated: 2022/10/25 15:15:57 by ycucchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SOURCES = main.c map_reader.c map_reader_utils.c map_reader_functions.c \
clean_all_helper.c struct_init.c room_array.c tab_array.c print.c \
print_result.c

CC = gcc
FLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./includes/
LIBFT_INC = -I ./libft/includes/

SRCS_PATH = srcs/
OBJ_DIR  = objects/
LIBFT_PATH = libft/
LIB_LFT = -L ./libft/ -lft

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)

DEFAULT = \033[0;39m
GRAY = \033[0;90m
GREEN = \033[0;92m
PURPLE = \033[0;94m

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(INCLUDES) $(LIB_LFT)
	@echo "$(GREEN)All good!$(DEFAULT)"

$(OBJ_DIR)%.o: $(SRCS_PATH)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(PURPLE)Compiling $(notdir $<)...$(DEFAULT)"
	@$(CC) -c $(FLAGS) $(LIBFT_INC) $(INCLUDES) $< -o $@
	@echo "$(GREEN)Compilation of $(notdir $<) done!$(DEFAULT)"

git:
	git add -A
	git commit -m "$m"
	git push

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GRAY)$(OBJ_DIR) cleaned!$(DEFAULT)"
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GRAY)$(NAME) cleaned!$(DEFAULT)"
	@make fclean -C $(LIBFT_PATH)
	@echo "$(GRAY)$(NAME) cleaned!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
