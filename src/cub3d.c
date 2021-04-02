#include "../include/cub3d.h"

int	end_game(t_game *game)
{
	endAudio();
	SDL_Quit();
	exit(1);
}

int	init_game(t_game *game)
{
    int i;


	if (!(game->manager.instance = mlx_init()))
		return (0);

	if (!(game->manager.window = mlx_new_window(game->manager.instance, game->res_width, game->res_height, "Pokemon 3D")))
		return (0);

	mlx_hook(game->manager.window, 2, 1L << 0, &onKeyPress, game);
	mlx_hook(game->manager.window, 3, 1L << 1, &onKeyRelease, game);
	mlx_hook(game->manager.window, 17, 0, &onWindowClose, game);
	mlx_mouse_hook(game->manager.window, &onMouseClick, game);
	mlx_loop_hook(game->manager.instance, &onGameLoop, game);
	i = 0;
	while (i++ < 270)
		game->manager.inputs[i - 1] = 0;
	return (TRUE);
}

int	load_textures(t_game *game)
{
	size_t i;

	i = 0;
	while (i < 9)
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
		if (!load_texture(game->manager.instance, &game->textures.frontsprite[i], game->settings.pkm_data[i].front_path))
			return (FALSE);
		if (!load_texture(game->manager.instance, &game->textures.backsprite[i], game->settings.pkm_data[i].back_path))
			return (FALSE);

		free(game->settings.pkm_data[i].front_path);
		free(game->settings.pkm_data[i].back_path);
		game->settings.pkm_data[i].front_path = NULL;
		game->settings.pkm_data[i].back_path = NULL;
		i++;
	}

	if (!load_texture(game->manager.instance, &game->textures.hud[0], "../resources/texture/hud/battle.png"))
		return (FALSE);

	if (!load_texture(game->manager.instance, &game->textures.hud[1], "../resources/texture/hud/pokeflaute.png"))
		return (FALSE);

	if (!load_texture(game->manager.instance, &game->textures.fonts[0], "../resources/font/basic.png"))
		return (FALSE);
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	return (TRUE);
}

int	run_game(t_game *game)
{
	game->gamestate = PLAYING;
	mlx_mouse_hide();
	playMusic("../resources/sounds/route42.wav", SDL_MIX_MAXVOLUME / 4);
	init_story(game);
	init_player(game->settings, &game->player, &game->animation);
	game->timer.last_update = current_milliseconds();
	mlx_loop(game->manager.instance);
	return (TRUE);
}
