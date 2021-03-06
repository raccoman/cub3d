# include "cub3d.h"

int				onWindowClose(t_game *game)
{
	return (1);
}

int				onKeyPress(int key, t_game *game)
{
	game->manager.inputs[key] = TRUE;
	return (1);
}

int				onKeyRelease(int key, t_game *game)
{
	game->manager.inputs[key] = FALSE;
	return (1);
}

int				onMouseClick(int button, int x, int y, t_game *game)
{
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
