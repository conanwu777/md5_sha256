NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = dispatch.c main.c md5.c sha256.c
OBJ = $(SRC1:.c=.o)
FT_LNK = -L ./libft -lft

all:
	make -C libft
	$(CC) $(CFLAGS) $(FT_LNK) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re:	fclean all
