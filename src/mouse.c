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
		max_rotatespeed = game->res_w * 0.5 / 1280.0;
		rotate_player(game, difference * max_rotatespeed / game->res_w);

		max_rotatespeed = game->res_w * 450 / 1280.0;
		game->player.yaw += (int) (difference * -max_rotatespeed / game->res_w);

		if (game->player.yaw > game->res_w)
			game->player.yaw = 0;
		if (game->player.yaw < 0)
			game->player.yaw = game->res_w;
	}

	if ((abs(difference = prevy - y)) > 0) {
		max_rotatespeed = game->res_h * 200.0 / 720.0;
		game->player.pitch = ft_clamp(game->player.pitch + (int) (difference * max_rotatespeed / game->res_h),200,-150);
	}

	if (y >= game->res_h)
	{
		y = 1;
		mlx_mouse_move(game->manager.window, x, y);
	}
	else if (y <= 0)
	{
		y = game->res_h - 1;
		mlx_mouse_move(game->manager.window, x, y);
	}
	if (x >= game->res_w) {
		x = 1;
		mlx_mouse_move(game->manager.window, x, y);
	}
	else if (x <= 0)
	{
		x = game->res_w - 1;
		mlx_mouse_move(game->manager.window, x, y);
	}

	prevx = x;
	prevy = y;
	return (TRUE);
}