# include "cub3d.h"

int	run_mouse_tick(t_game *game)
{
	int	x;
	int	y;
	int	difference;
	double		max_rotatespeed;
	static int	prevx;
	static int	prevy;

	mlx_mouse_get_pos(game->manager.window, &x, &y);

		if ((abs(difference = prevx - x)) > 0) {
			max_rotatespeed = game->res_width * 0.5 / 1280.0;
			rotate_player(game, difference * max_rotatespeed / game->res_width);

			max_rotatespeed = game->res_width * 450 / 1280.0;
			game->player.yaw += (int) (difference * -max_rotatespeed / game->res_width);

			if (game->player.yaw > game->res_width)
				game->player.yaw = 0;
			if (game->player.yaw < 0)
				game->player.yaw = game->res_width;
		}

		if ((abs(difference = prevy - y)) > 0) {
			max_rotatespeed = game->res_height * 200.0 / 720.0;
			game->player.pitch = ft_clamp(game->player.pitch + (int) (difference * max_rotatespeed / game->res_height),
										  200, -200);
		}

		if (y >= game->res_height)
		{
			y = 1;
			mlx_mouse_move(game->manager.window, x, y);
		}
		else if (y <= 0)
		{
			y = game->res_height - 1;
			mlx_mouse_move(game->manager.window, x, y);
		}
		if (x >= game->res_width) {
			x = 1;
			mlx_mouse_move(game->manager.window, x, y);
		}
		else if (x <= 0)
		{
			x = game->res_width - 1;
			mlx_mouse_move(game->manager.window, x, y);
		}

	prevx = x;
	prevy = y;
	return (TRUE);
}