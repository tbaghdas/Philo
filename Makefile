NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

SRC = simulation.c utils.c checking_and_parsing.c philo.c life_utils.c eat_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
