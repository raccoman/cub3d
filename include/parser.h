#ifndef PARSER_H
#define PARSER_H

# include "cub3D.h"
# include "gnl.h"
# include "libft.h"
# include <fcntl.h>

typedef enum	s_texture_path {
	NO_TEXTURE_PATH = 0,
	SO_TEXTURE_PATH = 1,
	WE_TEXTURE_PATH = 2,
	EA_TEXTURE_PATH = 3,
	F_TEXTURE_PATH = 4,
	C_TEXTURE_PATH = 5,
	S_BUSH_TEXTURE_PATH = 6,
	S_MT_TEXTURE_PATH = 7
}				t_texture_path;

int	parse_settings(t_game *game, const char *path);

#endif
