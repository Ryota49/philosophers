NAME	=	philo

CC	=		cc

CFLAGS	=	-Wall -Wextra -Werror

SOURCES	=	sources/create_and_join.c \
		 	sources/parsing.c \
		 	sources/philosophers.c \
			sources/routine.c  

OBJECTS =	$(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all clean fclean re
