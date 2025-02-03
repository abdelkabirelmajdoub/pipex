CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = 	src/pipex.c  src/pipex_utils.c src/parse.c

SRCB = 	src_bonus/pipex_bonus.c  \
		src_bonus/pipex_utils_bonus.c \
		src_bonus/open_fd_bonus.c \
		src_bonus/parse_bonus.c

GNL = 	src_bonus/GNL/get_next_line_bonus.c \
		src_bonus/GNL/get_next_line_utils_bonus.c

LIBFT = libft/libft.a
NAME = pipex

RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
NC     = \033[0m 

all:$(NAME)

$(NAME): $(SRC)
	@echo  "${YELLOW}Compiling files ...${NC}"
	@echo  "${BLUE}Waiting${NC}"
	@make all -C libft
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)
	@echo  "${GREEN}Compilation finished successfully!${NC}"

clean:
	@echo "${YELLOW} Cleaning .o files ...${NC}"
	@make clean -C libft
	@sleep 1
	@echo "${RED} Cleaned up!${NC}"

fclean: clean
	@echo "${YELLOW} Cleaning .o and ${NAME} files ...${NC}"
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "${RED} Cleaned up!${NC}"

re : fclean all

bonus: $(SRCB)
	@echo  "${YELLOW}Compiling files [Bonus]...${NC}"
	@echo  "${BLUE}Waiting${NC}"
	@make all -C libft
	$(CC) $(CFLAGS) $(SRCB) $(LIBFT) $(GNL) -o $(NAME)
	@echo  "${GREEN}Compilation finished successfully! [Bonus]${NC}"