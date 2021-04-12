#Name
NAME =					cub3D

#Compiler
CC = 			gcc
CFLAGS = 		-Wall -Wextra -Werror
LIBS =		$(MLX) -lm -framework OpenGL -framework AppKit $(GNL) $(ZLIB) $(SDL2DIR)/$(SDL2)
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
LIBFTDIR = 		./include/libft
MLXDIR = 		./include/mlx
ZLIBDIR = 		./include/zlib
GNLDIR =		./include/gnl
SDL2DIR =		./include/Library/Frameworks/SDL2.framework

#Libs
LIBFT = 		libft.a
MLXMMS = 		libmlx.dylib
MLX = 			libmlx.a
ZLIB =			libz.a
GNL = 			gnl.a
SDL2=			SDL2

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

INCLUDE :=	-I./include -I.include/libft -I.include/libmlx

#Srcs
SRCS =			$(foreach FILE, $(FILES), $(shell find $(SRCDIR) -name $(FILE)))

#Objs
OBJS =			$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.c=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(IFLAG) $(INCDIR) $(IFLAG) $(GNL) $(CFLAG) $(OFLAG) $@ $<

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL) $(MLX) $(ZLIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I $(MLX) $(LIBS) main.c $(OFLAG) $(NAME)

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
	@$(MAKE_CLEAN) $(LIBFTDIR)
	@$(MAKE_CLEAN) $(GNLDIR)
	@$(MAKE_CLEAN) $(MLXDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_FCLEAN) $(LIBFTDIR)
	@$(MAKE_CLEAN) $(GNLDIR)
	@$(MAKE_CLEAN) $(MLXDIR)

re: fclean all

.PHONY: all norminette clean fclean re
