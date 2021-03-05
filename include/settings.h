#ifndef SETTINGS_H
#define SETTINGS_H

# include <stdlib.h>

typedef struct	s_pokemon_data
{
	char	*name;
	char	*texture_path;
	char	*closeup_texture_path;
}				t_pokemon_data;

typedef struct	s_settings
{
	char			*env_texture_path[8];
	t_pokemon_data	pokemon_data[152];
	size_t			pokemon_count;
}				t_settings;

#endif
