SOURCES =   gnl.c \
            gnl_utils.c \

HEADERS =   gnl.h

NAME = gnl.a
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Werror -Wall -Wextra -c

.PHONY: all clean fclean re

%.o: %.c $(HEADERS)
	@ $(CC) -g $(CFLAGS) $<

$(NAME): $(OBJECTS)
	@ ar rc $(NAME) $(OBJECTS)
	@ ranlib $(NAME)

all: $(NAME)

bonus: $(NAME)

clean:
	@ rm -f $(OBJECTS)

fclean: clean
	@ rm -f $(NAME)

re: fclean all