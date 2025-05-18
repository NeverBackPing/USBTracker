#color
BLUE	=	\033[0;34m
GREEN	=	\033[0;32m
RED		=	\033[31m
RESET	=	\033[0m
YELLOW	=	\033[0;33m

# Compiler and Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Clear
RM = rm -rf

# Program
NAME = usbtracker

# Source
SRC = $(shell ls *.c)

OBJS = $(SRC:.c=.o)

# Fichier objet
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

define HEADER

██╗░░░██╗░██████╗██████╗░
██║░░░██║██╔════╝██╔══██╗
██║░░░██║╚█████╗░██████╦╝
██║░░░██║░╚═══██╗██╔══██╗
╚██████╔╝██████╔╝██████╦╝
░╚═════╝░╚═════╝░╚═════╝░
████████╗██████╗░░█████╗░░█████╗░██╗░░██╗███████╗██████╗░
╚══██╔══╝██╔══██╗██╔══██╗██╔══██╗██║░██╔╝██╔════╝██╔══██╗
░░░██║░░░██████╔╝███████║██║░░╚═╝█████═╝░█████╗░░██████╔╝
░░░██║░░░██╔══██╗██╔══██║██║░░██╗██╔═██╗░██╔══╝░░██╔══██╗
░░░██║░░░██║░░██║██║░░██║╚█████╔╝██║░╚██╗███████╗██║░░██║
░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝

endef
export HEADER

# Compile
all: $(NAME) 

header:
	@echo "$(GREEN)$$HEADER$(RESET)"

$(NAME): 	$(OBJS)
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) -ludev

run: header
	@./$(NAME)
clean:
			@$(RM) $(OBJS) $(NAME)

re: fclean all

.PHONY: all run clean fclean header re