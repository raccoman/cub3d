#ifndef SETTINGS_H
#define SETTINGS_H

# include "utils.h"
# include <stdlib.h>

typedef struct	s_pokemon_data
{
	char	*name;
	char	*front_path;
	char	*back_path;
}				t_pokemon_data;

typedef enum	e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_direction;

typedef struct	s_settings
{
	char			*env_texture_path[9];
	t_pokemon_data	pkm_data[152];
	size_t			pokemon_count;
	t_vector		spawn;
	t_direction		direction;
}				t_settings;

#endif
