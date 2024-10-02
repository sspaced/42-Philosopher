NAME = philosopher

CC = cc

CFLAGS = -g -Werror -Wextra -Wall #-fsanitize=thread

LIB = -pthread

INC = headers/philosopher.h

SRCS = 	main.c\
		src/parsing.c\
		src/display.c\
		src/init.c\
		src/philos_list.c\
		src/time_utils.c\
		src/free.c\
		src/thread.c\
		src/set.c\
		src/get.c\
		src/await.c\
		src/monitor.c\
		src/routine.c\
		src/action.c\

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