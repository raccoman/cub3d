#include "../headers/cub3d.h"
#include "../headers/texture.h"
/*
**	Norminette V3 Status: OK!
*/
int	end_game()
{
	endAudio();
	SDL_Quit();
	exit(1);
}

int	init_game(t_game *game)
{
	int	i;

	game->manager.instance = mlx_init();
	if (!(game->manager.instance))
		return (0);
	game->manager.window = mlx_new_window(game->manager.instance,
			game->res_w, game->res_h, "Pokemon 3D");
	if (!(game->manager.window))
		return (0);
	mlx_hook(game->manager.window, 2, 1L << 0, &onKeyPress, game);
	mlx_hook(game->manager.window, 3, 1L << 1, &onKeyRelease, game);
	mlx_hook(game->manager.window, 17, 0, &onWindowClose, game);
	mlx_mouse_hook(game->manager.window, ft_onmouse_click, game);
	mlx_loop_hook(game->manager.instance, &onGameLoop, game);
	i = 0;
	while (i++ < 270)
		game->manager.inputs[i - 1] = 0;
	return (TRUE);
}

int	load_textures(t_game *game)
{
	if (!ft_loadEnvironment(game))
		return (FALSE);
	if (!ft_loadPokemon(game))
		return (FALSE);
	if (!load_texture(game->manager.instance,
			&game->textures.hud[0],
			"./resources/texture/hud/battle.png"))
		return (FALSE);
	if (!load_texture(game->manager.instance,
			&game->textures.hud[1],
			"./resources/texture/hud/pokeflaute.png"))
		return (FALSE);
	if (!load_texture(game->manager.instance,
			&game->textures.fonts[0],
			"./resources/font/basic.png"))
		return (FALSE);
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	return (TRUE);
}

int	run_game(t_game *game)
{
	game->gamestate = PLAYING;
	mlx_mouse_hide();
	playMusic("./resources/sounds/route42.wav", SDL_MIX_MAXVOLUME / 4);
	init_story(game);
	init_player(game->settings, &game->player, &game->animation);
	game->timer.last_update = current_milliseconds();
	mlx_loop(game->manager.instance);
	return (TRUE);
}
