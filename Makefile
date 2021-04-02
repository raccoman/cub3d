#Name
NAME =					

#Compiler
CC = 			gcc
CFLAGS = 		-Wall -Wextra -Werror
CFLAG = 		-c
OFLAG =			-o
IFLAG =			-I

#Make
MAKE = 			make -C
MAKE_CLEAN = 	make clean -C
MAKE_FCLEAN = 	make fclean -C

#Norm
NORM =			norminette-V3

#Shell
MKDIR =			mkdir -p
CP =			cp
RM =			rm -rf

#Directories
SRCDIR = 		./src
OBJDIR =  		./objs
INCDIR = 		./include
LIBFTDIR = 		./include/libft

#Libs
LIBFT = 		libft.a

#Files
FILES =			cub3d.c battle.c hud.c key.c collisions.c events.c font.c mouse.c parser.c player.c raycaster.c renderer.c story.c texture.c timer.c utils.c world.c

#Srcs
SRCS = 			$(foreach FILE, $(FILES), $(shell find $(SRCDIR) -name $(FILE)))

#Objs
OBJS = 			$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.c=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(IFLAG) $(INCDIR) $(CFLAG) $(OFLAG) $@ $< 

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(OFLAG) $(NAME)

$(LIBFT):
	@$(MAKE) $(LIBFTDIR)
	@$(CP) $(LIBFTDIR)/$(LIBFT) .

norminette:
	@$(NORM) $(shell find $(SRCDIR) -name *.c)
	@$(NORM) $(shell find $(INCDIR) -name *.h)

clean:
	@$(RM) $(OBJDIR) $(OBJS) $(LIBFT) 
	@$(MAKE_CLEAN) $(LIBFTDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_FCLEAN) $(LIBFTDIR)

re: fclean all

.PHONY: all norminette clean fclean re