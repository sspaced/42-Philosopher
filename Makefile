NAME = philosopher

CC = cc

CFLAGS = -fsanitize=thread

LIB = -pthread

INC = headers/philosopher.h

SRCS = 	main.c\
		src/philo_handler.c\
		src/philo_init.c\
		src/philo_utils.c\
		src/philo_display.c\

OBJS =	$(SRCS:.c=.o)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -g $(CFLAGS) $(OBJS) $(LIB) -o $@

all: $(NAME)

clean:
		rm -rf $(OBJS)

fclean:
		rm -rf $(OBJS)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re