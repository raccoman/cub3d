#include "../headers/texture.h"
#include "../headers/cub3d.h"

int	load_texture(void *mlx_instance, t_texture_data *save_to, char *resource)
{
	if (!(save_to->image = mlx_png_file_to_image(mlx_instance, resource, &save_to->width, &save_to->height)))
		return (FALSE);
	save_to->address = mlx_get_data_addr(save_to->image, &save_to->bpp, &save_to->line_length, &save_to->endian);
	return (save_to->address != NULL);
}


int	ft_loadPokemon(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->settings.pokemon_count)
	{
		if (!load_texture(game->manager.instance,
						  &game->textures.frontsprite[i],
						  game->settings.pkm_data[i].front_path))
			return (FALSE);
		if (!load_texture(game->manager.instance,
						  &game->textures.backsprite[i],
						  game->settings.pkm_data[i].back_path))
			return (FALSE);
		free(game->settings.pkm_data[i].front_path);
		free(game->settings.pkm_data[i].back_path);
		game->settings.pkm_data[i].front_path = NULL;
		game->settings.pkm_data[i].back_path = NULL;
		i++;
	}
	return (TRUE);
}

int	ft_loadEnvironment(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < 9)
	{
		if (!load_texture(game->manager.instance,
						  &game->textures.environment[i],
						  game->settings.env_texture_path[i]))
			return (FALSE);
		free(game->settings.env_texture_path[i]);
		game->settings.env_texture_path[i] = NULL;
		i++;
	}
	return (TRUE);
}