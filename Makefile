#Name
NAME =					cub3D

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
NORM =			norminette

#Shell
MKDIR =			mkdir -p
CP =			cp
RM =			rm -rf

#Directories
SRCDIR = 		./src
OBJDIR =  		./objs
INCDIR = 		./include
LIBFTDIR = 		./libft
MLXDIR = 		./include/mlx
ZLIBDIR = 			./include/zlib
GNLDIR =			./include/gnl

#Libs
LIBFT = 		libft.a
MLX = 			libmlx.a
ZLIB =			libz.a
GNL = 			gnl.a

#Files
FILES =		cub3d.c \
			parser.c \
			texture.c \
			events.c \
			timer.c \
			world.c \
			renderer.c \
			utils.c \
			player.c \
			mouse.c \
			collisions.c \
			story.c \
			battle.c \
			font.c \
			hud.c \
			key.c \
			raycaster.c \
			sound.c \
			screenshot.c \
			battle_v3.c \
			mouse_event.c

#Srcs
SRCS =			$(foreach FILE, $(FILES), $(shell find $(SRCDIR) -name $(FILE)))

#Objs
OBJS =			$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.c=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(IFLAG) $(INCDIR) $(CFLAG) $(OFLAG) $@ $<

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL) $(ZLIB) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(OFLAG) $(NAME)

$(LIBFT):
	@$(MAKE) $(LIBFTDIR)
	@$(CP) $(LIBFTDIR)/$(LIBFT) .

$(ZLIB):
##	@$(MAKE) $(ZLIBDIR)
	@$(CP) $(ZLIBDIR)/$(ZLIB) .

$(MLX):
	@$(MAKE) $(MLXDIR)
	@$(CP) $(MLXDIR)/$(MLX) .

$(GNL):
	@$(MAKE) $(GNLDIR)
	@$(CP) $(GNLDIR)/$(GNL) .

norminette:
	@$(NORM) $(shell find $(SRCDIR) -name *.c)
	@$(NORM) $(shell find $(INCDIR) -name *.h)

clean:
	@$(RM) $(OBJDIR) $(OBJS) $(LIBFT) $(GNL) $(MLX) $(ZLIB)
	@$(MAKE_CLEAN) ./include/$(LIBFTDIR)
	@$(MAKE_CLEAN) $(GNLDIR)
	@$(MAKE_CLEAN) $(MLXDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_FCLEAN) ./include/$(LIBFTDIR)
	@$(MAKE_CLEAN) ./include/$(GNLDIR)
	@$(MAKE_CLEAN) ./include/$(MLXDIR)

re: fclean all

.PHONY: all norminette clean fclean re
