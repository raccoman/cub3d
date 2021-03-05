SOURCES =   atoi.c \
            is_digit.c \
            is_isspace.c \
            screen.c \
            skip_charset.c \
            clamp.c \
            contains_only.c \
            starts_with.c \
            contains.c \
            strdup.c \
            strlen.c \
            terminate_at.c \
            concatenate.c \

HEADERS =   libft.h

NAME = libft.a
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