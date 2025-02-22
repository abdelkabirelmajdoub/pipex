CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = 	src/pipex.c  src/pipex_utils.c src/parse.c


GNL = 	src_bonus/GNL/get_next_line_bonus.c \
		src_bonus/GNL/get_next_line_utils_bonus.c

LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)

NAME = pipex

RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
NC     = \033[0m 

all:$(NAME)

$(NAME): $(OBJ)
	@echo  "${YELLOW}Compiling files ...${NC}"
	@echo  "${BLUE}Waiting${NC}"
	@make all -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo  "${GREEN}Compilation finished successfully!${NC}"

clean:
	@echo "${YELLOW} Cleaning .o files ...${NC}"
	@make clean -C libft
	@make clean -C src_bonus
	@rm -rf $(OBJ)
	@echo "${RED} Cleaned up!${NC}"

fclean: clean
	@echo "${YELLOW} Cleaning .o and ${NAME} files ...${NC}"
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "${RED} Cleaned up!${NC}"

re : fclean all

bonus: $(SRCB)
	make all -C src_bonus