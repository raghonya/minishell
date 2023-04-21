NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

FILES = $(wildcard *.c)

OBJ = $(FILES:.c=.o)

all: $(NAME)

%.o: %.c libft.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re