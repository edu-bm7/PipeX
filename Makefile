# C Compiler (Clang-12)
CC := cc
# PipeX Variables
NAME := pipex
NAME_BONUS := .pipex_bonus.txt
INC_DIR := includes
OBJS_DIR := objects
BONUS_OBJS_DIR := bonus_objects
MANDATORY_DIR := mandatory
BONUS_DIR := bonus
# Libft Variables
LIBFT_DIR := libft
LIBFT := libft.a

CFLAGS = -Wall -Wextra -Werror -g3 -I$(LIBFT_DIR) -I$(INC_DIR)

SRCS = $(addprefix $(MANDATORY_DIR)/, main.c\
				forked_routine.c\
				pipe_utils.c\
				wait_for_processes.c\
				initialize_exec_variables.c\
				handle_quotes.c\
				handle_exec_errors.c\
		)

BONUS = $(addprefix $(BONUS_DIR)/, main_bonus.c\
        				forked_routine_bonus.c\
        				pipe_utils_bonus.c\
        				wait_for_processes_bonus.c\
        				initialize_exec_variables_bonus.c\
        				handle_quotes_bonus.c\
        				handle_exec_errors_bonus.c\
        				cmds_routine_bonus.c\
        				init_data_bonus.c\
        				here_doc_routine_bonus.c\
        		)

OBJS = $(patsubst $(MANDATORY_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
BONUS_OBJS = $(patsubst $(BONUS_DIR)%.c, $(BONUS_OBJS_DIR)%.o, $(BONUS))
# All Src subdirectories
SRC_SUBDIR := $(shell find $(MANDATORY_DIR) -type d)
BONUS_SUBDIR := $(shell find $(BONUS_DIR) -type d)
# Objects Subdirectories
OBJS_SUBDIR := $(subst $(MANDATORY_DIR), $(OBJS_DIR), $(SRC_SUBDIR))
BONUS_OBJS_SUBDIR := $(subst $(BONUS_DIR), $(BONUS_OBJS_DIR), $(BONUS_SUBDIR))

$(NAME): $(OBJS) | libft
	@if [ -d "$(BONUS_OBJS_DIR)" ]; then \
      		rm -rf $(BONUS_OBJS_DIR); \
      		rm -f $(NAME); \
      	fi
	@$(CC) $(OBJS) -o $@ -L$(LIBFT_DIR) -lft
	@echo "--------------------------"
	@echo "PipeX binary created."
	@echo "--------------------------"

$(NAME_BONUS): $(BONUS_OBJS) | libft
	@if [ -d "$(OBJS_DIR)" ]; then \
  		rm -rf $(OBJS_DIR); \
  		rm -f $(NAME); \
  	fi
	@$(CC) $(BONUS_OBJS) -o pipex -L$(LIBFT_DIR) -lft
	@touch $@
	@echo "--------------------------"
	@echo "PipeX binary created."
	@echo "--------------------------"

libft:
	@make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(MANDATORY_DIR)/%.c
	@if [ ! -d "$(OBJS_DIR)" ]; then \
		mkdir -p $(OBJS_SUBDIR); \
	fi
	@$(CC) $(CFLAGS) -c $? -o $@

$(BONUS_OBJS_DIR)/%.o: $(BONUS_DIR)/%.c
	@if [ ! -d "$(BONUS_OBJS_DIR)" ]; then \
		mkdir -p $(BONUS_OBJS_SUBDIR); \
	fi
	@$(CC) $(CFLAGS) -c $? -o $@


.PHONY: all clean fclean re log libft bonus

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(BONUS_OBJS_DIR)
	@echo "--------------------------"
	@echo "PipeX Objects removed."
	@echo "--------------------------"
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "PipeX removed."
	@echo "--------------------------"
	@make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: $(NAME_BONUS)

log:
	@echo "PipeX Source Files:" $(SRCS)
	@printf "\n"
	@echo "PipeX Objects Files:" $(OBJS)
	@printf "\n"