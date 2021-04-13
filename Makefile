#Name
NAME =			cub3D

#Compiler
CC = 			gcc
CFLAGS = 		-Wall -Wextra -Werror
FRAMEWORKS =	-framework OpenGL -framework AppKit $(SDL2_DIR)/$(SDL2)
LIBRARIES =		$(LIBFT_DIR)/$(LIBFT) $(MLX_DIR)/$(MLX) $(GNL_DIR)/$(GNL) $(ZLIB_DIR)/$(ZLIB) $(SOUND_DIR)/$(SOUND)
CFLAG = 		-c
OFLAG =			-o
IFLAG =			-I

#Make
MAKE = 			make -s -C
MAKE_CLEAN = 	make clean -s -C
MAKE_FCLEAN = 	make fclean -s -C

#Unzip
UNZIP =			unzip -X -o -q

#Norm
NORM =			norminette

#Shell
MKDIR =			mkdir -p
CP =			cp
RM =			rm -rf

#Directories
SOURCES_DIR = 	./src
OBJECTS_DIR =  	./objs
HEADERS_DIR = 	./headers
BUILD_DIR =		./build
LIBRARIES_DIR = ./libraries

LIBFT_DIR = 	./libraries/libft
MLX_DIR = 		./libraries/mlx
ZLIB_DIR = 		./libraries/zlib
GNL_DIR =		./libraries/gnl
SOUND_DIR =		./libraries/sound
SDL2_DIR =		./libraries/sdl2

#Libs
LIBFT = 	libft.a
MLX = 		libmlx.a
ZLIB =		libz.a
GNL =		gnl.a
SOUND =		sound.a
SDL2 =		SDL2.framework/SDL2

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
			screenshot.c \
			battle_v3.c \
			mouse_event.c

#Srcs
SRCS =			$(foreach FILE, $(FILES), $(shell find $(SOURCES_DIR) -name $(FILE)))

#Objs
OBJS =			$(patsubst $(SOURCES_DIR)/%, $(OBJECTS_DIR)/%, $(SRCS:.c=.o))

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(IFLAG) $(HEADERS_DIR) $(IFLAG) $(LIBRARIES_DIR) $(CFLAG) $(OFLAG) $@ $<

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(MLX) $(ZLIB) $(SDL2) $(SOUND) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FRAMEWORKS) $(LIBRARIES) main.c $(OFLAG) $(NAME)
	@echo "Done!"

$(LIBFT):
	@$(UNZIP) libraries/libft.zip -d libraries
	@$(MAKE) $(LIBFT_DIR)

$(ZLIB):
	@$(UNZIP) libraries/zlib.zip -d libraries
	@cd libraries/zlib; bash configure; make; cd ../../

$(MLX):
	@$(UNZIP) libraries/mlx.zip -d libraries
	@$(MAKE) $(MLX_DIR)

$(GNL):
	@$(UNZIP) libraries/gnl.zip -d libraries
	@$(MAKE) $(GNL_DIR)

$(SOUND):
	@$(UNZIP) libraries/sound.zip -d libraries
	@$(MAKE) $(SOUND_DIR)

$(SDL2):
	@$(UNZIP) libraries/sdl2.zip -d libraries

norminette:
	@$(NORM) $(shell find $(SOURCES_DIR) -name *.c)
	@$(NORM) $(shell find $(HEADERS_DIR) -name *.h)

clean:
	@$(RM) $(OBJECTS_DIR) $(LIBFT_DIR) $(GNL_DIR) $(MLX_DIR) $(ZLIB_DIR) $(SOUND_DIR) $(SDL2_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: all
	@./$(NAME) settings.cub

screenshot: all
	@./$(NAME) settings.cub --save

.PHONY: all screeshot norminette clean fclean re run
