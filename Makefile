SRC= main.c
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
		make clean -C libft
fclean: clean
		make fclean -C libft

