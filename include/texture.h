#ifndef TEXTURE_H
#define TEXTURE_H

# include "mlx.h"
# include "utils.h"
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
	t_texture_data hud[1];
	t_texture_data environment[8];
	t_texture_data pokemon[152];
	t_texture_data closeup_pokemon[152];
}				t_textures;

int				load_texture(void *mlx_instance, t_texture_data *save_to, char *resource);

#endif
