#include "cub3d.h"
#include "battle.h"

/*
**	Norminette V3 Status: OK!
*/

typedef enum e_nsprite
{
	BUSH = 6,
	BALL = 7,
	SNORLAX = 8,
}			t_nsprite;

int	onWindowClose()
{
	return (1);
}

/*
**	Debug:
**			printf("Key pressed: %d\n", key);
**			(line:  14, col:   5)
*/

int	onKeyPress(int key, t_game *game)
{
	if (key == KEY_ESC)
		end_game(game);
	game->manager.inputs[key] = TRUE;
	return (1);
}

int	onKeyRelease(int key, t_game *game)
{
	game->manager.inputs[key] = FALSE;
	return (1);
}

int	onGameLoop(t_game *game)
{
	int	i;

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
	if (sprite->texture_id == BUSH)
	{
		sprite->present = 0;
		ft_init_battle(game);
	}
	else if (sprite->texture_id == BALL && KEY_PRESSED(KEY_E))
	{
		playSound("./resources/sounds/found_pokeball.wav", SDL_MIX_MAXVOLUME);
		sprite->present = 0;
		game->story.pokeflaute = 1;
	}
	else if (sprite->texture_id == SNORLAX && KEY_PRESSED(KEY_E)
		&& game->story.pokeflaute && !game->story.pokeflaute_time)
	{
		playMusic("./resources/sounds/pokeflaute.wav", SDL_MIX_MAXVOLUME);
		game->story.pokeflaute_time = current_milliseconds();
	}
	return (1);
}
