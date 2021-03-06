# include "cub3d.h"

#define PLAYER game->player
#define IS_MOVING(x) game->manager.inputs[x]
#define COLLIDING_X_AXIS(x) game->map[(int)(x)][(int)PLAYER.posz]
#define COLLIDING_Z_AXIS(z) game->map[(int)PLAYER.posx][(int)(z)]

void	init_player(t_settings settings, t_player *player)
{
	player->posx = settings.spawn.x;
	player->posz = settings.spawn.z;

	if (settings.direction == NORTH)
	{
		player->dirx = -1;
		player->dirz = 0;
		player->planex = 0;
		player->planez = 0.66;
	}
	else if (settings.direction == SOUTH)
	{
		player->dirx = 1;
		player->dirz = 0;
		player->planex = 0;
		player->planez = -0.66;
	}
	else if (settings.direction == WEST)
	{
		player->dirx = 0;
		player->dirz = -1;
		player->planex = -0.66;
		player->planez = 0;
	}
	else if (settings.direction == EAST)
	{
		player->dirx = 0;
		player->dirz = 1;
		player->planex = 0.66;
		player->planez = 0;
	}


}

int		run_player_tick(t_game *game)
{
	double movespeed = 0.1;
	double rotatespeed = 0.1;

	if (IS_MOVING(KEY_W))
	{
		if (COLLIDING_X_AXIS(PLAYER.posx + PLAYER.dirx * movespeed * 3) == '0')
			PLAYER.posx += PLAYER.dirx * movespeed;

		if (COLLIDING_Z_AXIS(PLAYER.posz + PLAYER.dirz * movespeed * 3) == '0')
			PLAYER.posz += PLAYER.dirz * movespeed;
	}

	if (IS_MOVING(KEY_S))
	{
		if (COLLIDING_X_AXIS(PLAYER.posx - PLAYER.dirx * movespeed * 0.8 * 3) == '0')
			PLAYER.posx -= PLAYER.dirx * movespeed * 0.8;

		if (COLLIDING_Z_AXIS(PLAYER.posz - PLAYER.dirz * movespeed * 0.8 * 3) == '0')
			PLAYER.posz -= PLAYER.dirz * movespeed * 0.8;
	}

	if (IS_MOVING(KEY_D))
	{
		if (COLLIDING_Z_AXIS(PLAYER.posz + PLAYER.dirx * -movespeed * 3) == '0')
			PLAYER.posz += PLAYER.dirx * -movespeed;
		if (COLLIDING_X_AXIS(PLAYER.posx + PLAYER.dirz * movespeed * 3) == '0')
			PLAYER.posx += PLAYER.dirz * movespeed;
	}

	if (IS_MOVING(KEY_A))
	{
		if (COLLIDING_Z_AXIS(PLAYER.posz - PLAYER.dirx * -movespeed * 3) == '0')
			PLAYER.posz -= PLAYER.dirx * -movespeed;
		if (COLLIDING_X_AXIS(PLAYER.posx - PLAYER.dirz * movespeed * 3) == '0')
			PLAYER.posx -= PLAYER.dirz * movespeed;
	}

	if (IS_MOVING(KEY_R_ARROW))
	{
		rotate_player(game, -rotatespeed);
	}

	if (IS_MOVING(KEY_L_ARROW))
	{
		rotate_player(game, rotatespeed);
	}

	return (TRUE);
}

int		rotate_player(t_game *game, double rotatespeed)
{
	double lastdirx;
	double lastplanex;

	lastdirx = PLAYER.dirx;
	PLAYER.dirx = PLAYER.dirx * cos(rotatespeed) - PLAYER.dirz * sin(rotatespeed);
	PLAYER.dirz = lastdirx * sin(rotatespeed) + PLAYER.dirz * cos(rotatespeed);
	lastplanex = PLAYER.planex;
	PLAYER.planex = PLAYER.planex * cos(rotatespeed) - PLAYER.planez * sin(rotatespeed);
	PLAYER.planez = lastplanex * sin(rotatespeed) + PLAYER.planez * cos(rotatespeed);
	return (TRUE);
}