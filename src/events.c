# include "cub3d.h"

int				onWindowClose(t_game *game)
{
	return (1);
}

int				onKeyPress(int key, t_game *game)
{
	if (key == KEY_ESC)
		end_game(game);

	game->manager.inputs[key] = TRUE;
	//printf("Key pressed: %d\n", key);
	return (1);
}

int				onKeyRelease(int key, t_game *game)
{
	game->manager.inputs[key] = FALSE;
	return (1);
}

int				onMouseClick(int button, int x, int y, t_game *game)
{

	if (game->gamestate == FIGHTING)
	{
		// Click RUN button
		if (x >= game->res_width / 2 + game->res_width / 2 / 2 && x <= game->res_width &&
			y >= game->res_height / 3 * 2 + game->res_height / 3 / 2 && y <= game->res_height)
		{
			mlx_mouse_hide();
			game->gamestate = PLAYING;
			playMusic("../resources/sounds/route42.wav", SDL_MIX_MAXVOLUME / 4);
		}

		//Click catch button
		if (x >= game->res_width / 2 && x <= game->res_width / 2  + game->res_width / 2 / 2 &&
			y >= game->res_height / 3 * 2 + game->res_height / 3 / 2 && y <= game->res_height)
		{

			if (game->story.alive && game->story.atk_turn == 0 && (current_milliseconds() - game->story.atk_time) > 2000L) {
				playSound("../resources/sounds/pokemon_wiggle.wav", SDL_MIX_MAXVOLUME * 4);
				game->story.catching = 1;
				game->story.catching_time = current_milliseconds();
			}


		}

		//Click fight button
		if (x >= game->res_width / 2 && x <= game->res_width / 2  + game->res_width / 2 / 2 &&
			y >= game->res_height / 3 * 2 && y <= game->res_height / 3 * 2 + game->res_height / 3 / 2)
		{

			if (game->story.alive && game->story.atk_turn == 0 && (current_milliseconds() - game->story.atk_time) > 2000L)
				attack_opponent(game);
		}
	}

	//printf("Key pressed: %d Position: %d %d\n", button, x, y);
	return (1);
}

int				onGameLoop(t_game *game)
{
	int i;

	i = 0;
	update_timer(&game->timer);
	while (i < game->timer.elapsed_ticks)
	{
		if (!run_tick(game))
			return (FALSE);
		i++;
	}
	return (1);
}

int	onCollideSprite(t_game *game, t_sprite *sprite)
{
	if (sprite->texture_id == 6) // Colliding bush
	{
		sprite->present = 0;
		init_battle(game);
	}
	else if (sprite->texture_id == 7 && KEY_PRESSED(KEY_E)) //Colliding masterball
	{
		playSound("../resources/sounds/found_pokeball.wav", SDL_MIX_MAXVOLUME);
		sprite->present = 0;
		game->story.pokeflaute = 1;
	}
	else if (sprite->texture_id == 8 && KEY_PRESSED(KEY_E) && game->story.pokeflaute && !game->story.pokeflaute_time) //Colliding snorlax
	{
		playMusic("../resources/sounds/pokeflaute.wav", SDL_MIX_MAXVOLUME);
		game->story.pokeflaute_time = current_milliseconds();
	}

	return (1);
}