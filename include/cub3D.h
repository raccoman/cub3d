#ifndef CUB3D_H
#define CUB3D_H

# include "utils.h"

typedef struct	s_settings
{
}				t_settings;

typedef struct	s_game
{
	int			res_height;
	int			res_width;
	t_settings	settings;
}				t_game;

int				run_game(t_game *game);

#endif
