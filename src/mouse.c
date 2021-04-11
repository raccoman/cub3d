#include "cub3d.h"

int	run_mouse_tick(t_game *game)
{
	t_vector	vector;
	int			difference;
	double		max_rotatespeed;
	static int	prevx;
	static int	prevy;

	mlx_mouse_get_pos(game->manager.window, (int *)&vector.x, (int *)&vector.z);
	difference = prevx - (int)vector.x;
	if (abs(difference) > 0)
	{
		max_rotatespeed = game->res_w * 0.5 / 1280.0;
		rotate_player(game, difference * max_rotatespeed / game->res_w);
		max_rotatespeed = game->res_w * 450 / 1280.0;
		game->player.yaw += (int)(difference * -max_rotatespeed / game->res_w);
		if (game->player.yaw > game->res_w)
			game->player.yaw = 0;
		if (game->player.yaw < 0)
			game->player.yaw = game->res_w;
	}
	difference = prevy - (int)vector.z;
	if (abs(difference) > 0)
	{
		max_rotatespeed = game->res_h * 200.0 / 720.0;
		game->player.pitch = ft_clamp(game->player.pitch + (int) (difference * max_rotatespeed / game->res_h), 200, -150);
	}
	if (vector.z >= game->res_h)
	{
		vector.z = 1;
		mlx_mouse_move(game->manager.window, (int)vector.x, (int)vector.z);
	}
	else if (vector.z <= 0)
	{
		vector.z = game->res_h - 1;
		mlx_mouse_move(game->manager.window, (int)vector.x, (int)vector.z);
	}
	if (vector.x >= game->res_w) {
		vector.x = 1;
		mlx_mouse_move(game->manager.window, (int)vector.x, (int)vector.z);
	}
	else if (vector.x <= 0)
	{
		vector.x = game->res_w - 1;
		mlx_mouse_move(game->manager.window, (int)vector.x, (int)vector.z);
	}
	prevx = (int)vector.x;
	prevy = (int)vector.z;
	return (TRUE);
}