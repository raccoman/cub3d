SOURCES =   sound.c
HEADERS =   sound.h

NAME = sound.a
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Werror -Wall -Wextra -c

.PHONY: all clean fclean re

%.o: %.c $(HEADERS)
	@ $(CC) -g $(CFLAGS) -framework OpenGL -framework AppKit $<

$(NAME): $(OBJECTS)
	@ ar rc $(NAME) $(OBJECTS)
	@ ranlib $(NAME)

all: $(NAME)

clean:
	@ rm -f $(OBJECTS)

fclean: clean
	@ rm -f $(NAME)

re: fclean all