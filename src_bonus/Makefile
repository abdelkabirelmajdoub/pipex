CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCB = 	pipex_bonus.c  \
		pipex_utils_bonus.c \
		open_fd_bonus.c \
		parse_bonus.c

GNL = 	GNL/get_next_line_bonus.c \
		GNL/get_next_line_utils_bonus.c
LIBFT = ../libft/libft.a

NAME = ../pipex

OBJB = $(SRCB:.c=.o)

RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
NC     = \033[0m 

all: $(NAME)

$(NAME): $(OBJB)
	@echo  "${YELLOW}Compiling files [Bonus]...${NC}"
	@echo  "${BLUE}Waiting${NC}"
	@make all -C ../libft
	$(CC) $(CFLAGS) $(OBJB) $(LIBFT) $(GNL) -o $(NAME)
	@echo  "${GREEN}Compilation finished successfully! [Bonus]${NC}"

%.o:%.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C ../libft
	rm -rf $(OBJB)

fclean : clean
	rm -rf $(NAME)

re: fclean all