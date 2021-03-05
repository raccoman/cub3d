#ifndef CUB3D_H
#define CUB3D_H

# include "settings.h"
# include "texture.h"
# include "utils.h"

typedef struct	s_manager
{
	void	*instance;
	void	*window;
	short	inputs[270];
}				t_manager;

typedef struct	s_game
{
	int	res_height;
	int	res_width;

	signed char 	**map;

	t_textures		textures;
	t_settings		settings;
	t_manager		manager;
}				t_game;

int				onWindowClose(t_game *game);
int				onKeyPress(int key, t_game *game);
int				onKeyRelease(int key, t_game *game);
int				onMouseClick(int button, int x, int y, t_game *game);

int				init_game(t_game *game);

int				load_textures(t_game *game);

int				run_game(t_game *game);

#endif
