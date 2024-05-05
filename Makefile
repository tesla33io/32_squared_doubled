#### MAIN SETTINGS ####

# Compiler to be used
CC				:= cc -g

# Compiler flags
CFLAGS			:= #-Wall -Werror -Wextra #-pedantic -O3

# Libraries to be linked (if any)
LIBS			:= -lncurses

# Include directories
INCLUDES		:= -Iinc/

# Target executable
NAME			:= 2048

# Source files directory
SRC_DIR			:= tui_bonus/

# Source files
SRC_FILES		+= main.c

# Object files directory
OBJ_DIR			:= obj/

# Object files
OBJ_FILES		:= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC_FILES))

# Dependency files directory
DEP_DIR			:= dep/

# Dependency files
DEPENDS			:= $(patsubst %.o, $(DEP_DIR)%.d, $(OBJ_FILES))
-include $(DEPENDS)

#### SHELL COMMANDS ####

RM				:= /bin/rm -f
MKDIR			:= /bin/mkdir -p
TOUCH			:= /bin/touch

#### SPECIAL VARIABLES ####

BONUS			?= 1

#### LOCAL LIBRARIES ####

## FT_PRINTF_PATH	:= ft_printf/
## FT_PRINTF_LIB	:= $(FT_PRINTF_PATH)libftprintf.a

## LIBFT_PATH		:= libft/
## LIBFT_LIB		:= $(LIBFT_PATH)libft.a

#### DEBUG SETTINGS ####

ifeq ($(DEBUG), 1)
	CFLAGS		+= -g3 -O0
endif

#### TARGET COMPILATION ####

.DEFAULT_GOAL	:= all

all: $(NAME) ## Build this project

# Compilation rule for object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(MKDIR) $(@D)
	@echo "$(BLUE)[$(NAME) -" \
	"build]:$(CYAN)" \
	"$(BOLD)compile$(RESET)$(CYAN) $@ $(RESET)"
	@$(CC) $(CFLAGS) -DWITH_BONUS=$(BONUS) -MMD -MF $(patsubst %.o, %.d, $@) $(INCLUDES) -c $< -o $@ 

# Rule for linking the target executable
$(NAME): $(OBJ_FILES)
##	@echo $(BONUS)
	@echo "$(BLUE)[$(NAME) -" \
	"build]:$(GREEN)" \
	"$(BOLD)Link$(RESET)$(GREEN) $(NAME) $(RESET)"
	$(CC) $(CFLAGS) -DWITH_BONUS=$(BONUS) -o $(NAME) $(OBJ_FILES) $(INCLUDES) $(LIBS)
	@echo "$(BLUE)[$(NAME) -" \
	"info]: $(GREEN)$(BOLD)Build finished!$(RESET)"
	-@echo -n "$(MAGENTA)" && ls -lah $(NAME) && echo -n "$(RESET)"

bonus: ## Run program with bonus part
	BONUS ?= 1
	$(MAKE)

#### LOCAL LIBS COMPILATION ####

## $(FT_PRINTF_LIB):
## 	@$(MAKE) -sC $(FT_PRINTF_PATH)

## $(LIBFT_LIB):
## 	@$(MAKE) -C $(LIBFT_PATH)

#### ADDITIONAL RULES ####

clean: ## Clean objects and dependencies
	@$(RM) $(OBJ_FILES)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(BLUE)[$(NAME) -" \
	"clean]: $(YELLOW)$(BOLD)Remove objects$(RESET)"
	@$(RM) $(DEPENDS)
	@$(RM) -r $(DEP_DIR)
	@echo "$(BLUE)[$(NAME) -" \
	"clean]: $(YELLOW)$(BOLD)Remove dependecies$(RESET)"
## 	@(test -s $(LIBFT_LIB) && $(MAKE) -C $(LIBFT_PATH) clean) ||:

fclean: clean ## Restore project to initial state
	@$(RM) $(NAME)
	@echo "$(BLUE)[$(NAME) -" \
	"fclean]:$(YELLOW)" \
	"$(BOLD)Remove$(RESET)$(YELLOW) \`$(NAME)\`$(RESET)"
##	@(test -s $(LIBFT_LIB) && $(MAKE) -C $(LIBFT_PATH) fclean) ||:

re: fclean all ## Rebuild project

run:
	valgrind --suppressions=2048.supp --leak-check=full --show-leak-kinds=all ./2048

help: ## Show help info
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "$(CYAN)%-30s$(RESET) %s\n", $$1, $$2}'

.PHONY: all re clean fclean help bonus

#### COLORS ####
# Color codes
RESET		:= \033[0m
BOLD		:= \033[1m
UNDERLINE	:= \033[4m

# Regular colors
BLACK		:= \033[30m
RED			:= \033[31m
GREEN		:= \033[32m
YELLOW		:= \033[33m
BLUE		:= \033[34m
MAGENTA		:= \033[35m
CYAN		:= \033[36m
WHITE		:= \033[37m

# Background colors
BG_BLACK	:= \033[40m
BG_RED		:= \033[41m
BG_GREEN	:= \033[42m
BG_YELLOW	:= \033[43m
BG_BLUE		:= \033[44m
BG_MAGENTA	:= \033[45m
BG_CYAN		:= \033[46m
BG_WHITE	:= \033[47m
