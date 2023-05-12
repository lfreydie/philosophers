# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:01:41 by lfreydie          #+#    #+#              #
#    Updated: 2023/05/12 12:09:38 by lfreydie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------- Project ---------- #

CC ?= gcc
NAME := philo
NAME_B := philo_bonus
CFLAGS += -Wall -Wextra -Werror -pthread -g

# -------- Directories -------- #

HD_DIR = ./include
HD_DIR_BONUS = ./philo_bonus/include
SRC_DIR = ./src
OBJ_DIR = ./objs
BONUS_DIR = ./philo_bonus/src
BONUS_O_DIR = ./philo_bonus/objs

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

SRC_F =	philo.c	utils.c	init.c	exit.c	activities.c	time.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_F))
OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

# BONUS_F =	pipex.c	utils.c	exec.c exit.c
# BONUS = $(addprefix $(BONUS_DIR)/, $(BONUS_F))
# BONUS_O = $(patsubst $(BONUS_DIR)/%,$(BONUS_O_DIR)/%,$(BONUS:.c=.o))

# --------- Compiles ---------- #

$(NAME) :	$(OBJ)
	@echo "$(BLUE) ==== Project compiling ==== $(END)"
	@$(CC) $(CFLAGS) -I $(HD_DIR) $(OBJ) -o $(NAME)
	@echo "$(GREEN) ==== Project compiled ==== $(END)"

# $(NAME_B) :	$(BONUS_O)
# 	@echo "$(BLUE) ==== Bonus compiling ==== $(END)"
# 	@$(CC) $(CFLAGS) -I $(HD_DIR_BONUS) $(BONUS_O) -o $(NAME_B)
# 	@echo "$(GREEN) ==== Bonus compiled ==== $(END)"

# ----------- Link ------------ #

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HD_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(HD_DIR) -c $< -o $@

# $(BONUS_O_DIR)/%.o : $(OBJ_DIR)/%.c $(HD_DIR_BONUS)
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) -I $(HD_DIR_BONUS) -c $< -o $@

# ----------- Rules ----------- #

all :	$(NAME)

clean :
	@$(RM) $(RM_OPT) $(OBJ_DIR)
	# @$(RM) $(RM_OPT) $(BONUS_O_DIR)
	@echo "$(PINK) ==== All object removed ==== $(END)"

fclean :	clean
	@$(RM) $(NAME)
	# @$(RM) $(NAME_B)
	@echo "$(RED) ==== Executables removed ==== $(END)"

scan :
	@echo "	$(BLUE) ==== Scan running ==== $(END)"
	@scan-build-12 make -s
	@echo "	$(GREEN) ==== Scan finished ==== $(END)"

re :	fclean all

.PHONY : all clean fclean scan re
