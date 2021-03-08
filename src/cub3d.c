#include "cub3d.h"

int	init_game(t_game *game)
{
	if (!(game->manager.instance = mlx_init()))
		return (0);

	if (!(game->manager.window = mlx_new_window(game->manager.instance, game->res_width, game->res_height, "Pokemon 3D")))
		return (0);

	mlx_hook(game->manager.window, 2, 1L << 0, &onKeyPress, game);
	mlx_hook(game->manager.window, 3, 1L << 1, &onKeyRelease, game);
	mlx_hook(game->manager.window, 17, 0, &onWindowClose, game);
	mlx_mouse_hook(game->manager.window, &onMouseClick, game);
	mlx_loop_hook(game->manager.instance, &onGameLoop, game);
	mlx_mouse_hide();
	return (TRUE);
}

int	load_textures(t_game *game)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (!load_texture(game->manager.instance, &game->textures.environment[i], game->settings.env_texture_path[i]))
			return (FALSE);

		free(game->settings.env_texture_path[i]);
		game->settings.env_texture_path[i] = NULL;
		i++;
	}
	i = 0;
	while (i < game->settings.pokemon_count)
	{
		if (!load_texture(game->manager.instance, &game->textures.pokemon[i], game->settings.pokemon_data[i].texture_path))
			return (FALSE);
		if (!load_texture(game->manager.instance, &game->textures.closeup_pokemon[i], game->settings.pokemon_data[i].closeup_texture_path))
			return (FALSE);

		free(game->settings.pokemon_data[i].texture_path);
		free(game->settings.pokemon_data[i].closeup_texture_path);
		game->settings.pokemon_data[i].texture_path = NULL;
		game->settings.pokemon_data[i].closeup_texture_path = NULL;
		i++;
	}
	return (TRUE);
}

int	run_game(t_game *game)
{
	init_player(game->settings, &game->player, &game->animation);
	game->timer.last_update = current_milliseconds();
	mlx_loop(game->manager.instance);
	return (TRUE);
}

