# SRC= main.c pipex.c parser.c error.c
# NAME= pipex
# OBJS= $(SRC:.c=.o)
# CC= cc
# CFLAGS = -Wall -Werror -Wextra
# all: $(NAME)
# 
# $(NAME): $(addprefix src/,$(OBJS))
# make -C libft
# $(CC) $^ -L libft -l ft -o $(NAME)
# %.o: %.c
# $(CC) -c $(CFLAGS) $< -o $@
# 
# clean:
# rm -f $(addprefix src/,$(OBJS))
# make clean -C libft
# fclean: clean
# rm -f $(NAME)
# make fclean -C libft
# 
# 
SRC= main.c pipex.c parser.c error.c
BONUS = main.c pipex_bonus.c parser.c error.c pipex_utils.c
NAME= pipex
OBJS= $(SRC:.c=.o)
OBJS_BONUS= $(BONUS:.c=.o)
CC= cc
CFLAGS = -Wall -Werror -Wextra
all: $(NAME)

bonus: $(addprefix src/,$(OBJS_BONUS))
		make -C libft
		$(CC) $(CFLAGS) $^ -L libft -l ft -o $(NAME)

$(NAME): $(addprefix src/,$(OBJS))
		make -C libft
		$(CC) $(CFLAGS) $^ -L libft -l ft -o $(NAME)
%.o: %.c
	$(CC) -c $< -o $@

clean:
		rm -f $(addprefix src/,$(OBJS)) $(addprefix src/,$(OBJS_BONUS)) 
		make clean -C libft
fclean: clean
		rm -f $(NAME)
		make fclean -C libft

