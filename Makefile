SRC= main.c pipex.c parser.c error.c
NAME= pipex
OBJS= $(SRC:.c=.o)
CC= cc
CFLAGS = -Wall -Werror -Wextra
all: $(NAME)

$(NAME): $(addprefix src/,$(OBJS))
		make -C libft
		$(CC) $^ -L libft -l ft -o $(NAME)
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
		rm -f $(addprefix src/,$(OBJS))
		make clean -C libft
fclean: clean
		rm -f $(NAME)
		make fclean -C libft

