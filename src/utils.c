#include "utils.h"
#include "cub3d.h"
#include "sound.h"

t_vector	vector(double x, double z)
{
	t_vector vector;

	vector.x = x;
	vector.z = z;
	return (vector);
}

int64_t	hp_to_color(int hp)
{
	if (hp >= 50)
		return (0x2CC91E);
	else if (hp >= 20)
		return (0xF2BA35);
	else
		return (0xAD271D);
}

/*
int		screenshot(t_game *game)
{
	update_screen(game);
	update_ui(game);
	update_window(game);
	if (!save_bmp(game))
		exit_error(game, "Error:\nfailed to save screenshot.");
	return (exit_game(game, EXIT_SUCCESS));
}*/
