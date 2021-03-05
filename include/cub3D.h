#ifndef CUB3D_H
#define CUB3D_H

# include "settings.h"
# include "texture.h"
# include "utils.h"

typedef struct	s_rendering
{
	t_texture_data env_textures[8];
}				t_rendering;

typedef struct	s_game
{
	unsigned int	res_height;
	unsigned int	res_width;

	signed char 	**map;

	t_rendering		rendering;
	t_settings		settings;
}				t_game;

int				run_game(t_game *game);

#endif
