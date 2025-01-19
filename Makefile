
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c pipex_utils.c
NAME = pipex

all:$(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)
fclean:
	rm -rf $(NAME) 

re : fclean all