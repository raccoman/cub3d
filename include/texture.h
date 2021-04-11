#ifndef TEXTURE_H
#define TEXTURE_H

# include "mlx.h"
# include "utils.h"
# include "cub3d.h"
# include <stdlib.h>

int				load_texture(void *mlx_instance, t_texture_data *save_to, char *resource);
int 			ft_loadPokemon(t_game *game);
int 			ft_loadEnvironment(t_game *game);

#endif
