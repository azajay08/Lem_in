# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajones <ajones@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 00:15:54 by ajones            #+#    #+#              #
#    Updated: 2022/10/24 14:03:18 by ajones           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lem-in

#FLAGS:
FLAGS := -Wall -Werror -Wextra

#INCLUDES:
F_INC := -I./includes/
L_INC := -I./libft/
LIBFT := libft/libft.a
LIB := -L./libft/ -lft

#SOURCES:
SRCS := l_main.c l_init.c l_errors.c l_read_input.c
SRC_P := ./srcs/
F_SRC := $(addprefix $(SRC_P), $(SRCS))

#OBJECTS:
O_FILES := $(SRCS:%.c=%.o)
O_PATH := ./obj/
O_DIR := $(addprefix $(O_PATH), $(O_FILES))

#COLORS:
GREEN := '\033[1;3;32m'
CYAN := '\033[2;3;36m'
RED := '\033[2;3;31m'
RESET := \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(O_PATH) $(O_DIR)
	@echo ${CYAN}"Making $(@) executable...${RESET}"
	@gcc $(FLAGS) $(F_INC) $(L_INC) $(O_DIR) $(LIB) -o $(NAME)
	@echo ${GREEN}"Executable successfully made${RESET}"

$(LIBFT):
	@make -C libft

$(O_PATH):
	@mkdir -p $(O_PATH)

$(O_PATH)%.o: $(SRC_P)%.c
	@gcc -c $(FLAGS) $(F_INC) $(L_INC)  -o $@ $<

clean:
	@echo ${RED}"Removing obj directory...${RESET}"
	@rm -rf $(O_PATH)
	@make -C libft clean

fclean: clean
	@echo ${RED}"Removing $(NAME)...${RESET}"
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY := all re clean fclean make