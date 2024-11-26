NAME = philo
CC = gcc -pthread
CFLAGS = -Wall -Wextra
SRCS = main.c utils.c init_mutex.c philo_actions.c timer.c create_threads.c monitoring_threads.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all