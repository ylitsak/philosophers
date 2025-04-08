# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 10:36:03 by saylital          #+#    #+#              #
#    Updated: 2025/04/08 18:13:22 by saylital         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -pthread
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c utils.c init_mutex.c philo_actions.c timer.c create_threads.c \
		monitoring_threads.c print_message.c
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