# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:01:41 by lfreydie          #+#    #+#              #
#    Updated: 2023/09/20 18:34:29 by lfreydie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------- Project ---------- #

CC ?= gcc
NAME := philo_bonus
CFLAGS += -Wall -Wextra -Werror -pthread -g

# -------- Directories -------- #

HD_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./objs

# ---------- Delete ----------- #

RM = rm -f
RM_OPT = -r

# ---------- Colors ----------- #

GREEN=\033[0;32m
BLUE=\033[0;34m
RED=\033[0;31m
PINK=\033[0;35m
END=\033[0m

# ----------- Files ----------- #

SRC_F =	main.c init.c	exit.c \
		philo_life/eat.c	philo_life/thread.c	philo_life/philo.c	philo_life/dead.c \
		print/print_helper.c	print/print_status.c \
		utils/ft_lib.c	utils/time.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_F))
OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

# --------- Compiles ---------- #

$(NAME) :	$(OBJ)
	@echo "$(BLUE) ==== Project compiling ==== $(END)"
	@$(CC) $(CFLAGS) -I $(HD_DIR) $(OBJ) -o $(NAME)
	@echo "$(GREEN) ==== Project compiled ==== $(END)"

# ----------- Link ------------ #

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HD_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(HD_DIR) -c $< -o $@

# ----------- Rules ----------- #

all :	$(NAME)

clean :
	@$(RM) $(RM_OPT) $(OBJ_DIR)
	@echo "$(PINK) ==== All object removed ==== $(END)"

fclean :	clean
	@$(RM) $(NAME)
	@echo "$(RED) ==== Executables removed ==== $(END)"

scan :
	@echo "	$(BLUE) ==== Scan running ==== $(END)"
	@scan-build-12 make -s
	@echo "	$(GREEN) ==== Scan finished ==== $(END)"

re :	fclean all

.PHONY : all clean fclean scan re
