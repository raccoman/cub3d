#ifndef TEXTURE_H
#define TEXTURE_H

# include "mlx.h"
# include "utils.h"
# include "cub3d.h"
# include <stdlib.h>

typedef struct	s_texture_data
{
	void	*image;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_texture_data;

typedef struct	s_textures
{
	t_texture_data fonts[1];
	t_texture_data hud[2];
	t_texture_data environment[9];
	t_texture_data frontsprite[152];
	t_texture_data backsprite[152];
}				t_textures;

int				load_texture(void *mlx_instance, t_texture_data *save_to, char *resource);
int 			ft_loadPokemon(t_game *game);
int 			ft_loadEnvironment(t_game *game);

#endif
