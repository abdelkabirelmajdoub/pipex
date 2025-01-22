CC = gcc
CFLAGS = -Wall -Wextra -Werror 
SRC = 	src/pipex.c  src/pipex_utils.c 

SRCB = 	src_bonus/pipex_bonus.c  \
		src_bonus/pipex_utils_bonus.c 

GNL = 	src_bonus/GNL/get_next_line_bonus.c \
		src_bonus/GNL/get_next_line_utils_bonus.c

LIBFT = libft/libft.a

NAME = pipex

all:$(NAME)

$(NAME): $(SRC)
	make all -C libft
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

clean:
	make clean -C libft
	rm -rf $(NAME)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME) 

re : fclean all

bonus: $(SRCB)
	make all -C libft
	$(CC) $(CFLAGS) $(SRCB) $(LIBFT) $(GNL) -o $(NAME)