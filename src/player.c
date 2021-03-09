# include "cub3d.h"

#define PLAYER game->player
#define IS_MOVING(x) game->manager.inputs[x]
#define COLLIDING_X_AXIS(x) is_colliding(game, (int)(x), (int)PLAYER.posz)
#define COLLIDING_Z_AXIS(z) is_colliding(game, (int)PLAYER.posx, (int)(z))

void	init_player(t_settings settings, t_player *player, t_animation *animation)
{
	player->posx = settings.spawn.x;
	player->posz = settings.spawn.z;
	player->posy = 0;

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

	player->rotatespeed = 0.1;
	player->movespeed = 0.1;
	animation->walking = 0;
}

int		run_player_tick(t_game *game)
{

	if (IS_MOVING(KEY_W))
	{
		if (!COLLIDING_X_AXIS(PLAYER.posx + PLAYER.dirx * PLAYER.movespeed * 3))
			PLAYER.posx += PLAYER.dirx * PLAYER.movespeed;

		if (!COLLIDING_Z_AXIS(PLAYER.posz + PLAYER.dirz * PLAYER.movespeed * 3))
			PLAYER.posz += PLAYER.dirz * PLAYER.movespeed;
	}

	if (IS_MOVING(KEY_S))
	{
		if (!COLLIDING_X_AXIS(PLAYER.posx - PLAYER.dirx * PLAYER.movespeed * 0.8 * 3))
			PLAYER.posx -= PLAYER.dirx * PLAYER.movespeed * 0.8;

		if (!COLLIDING_Z_AXIS(PLAYER.posz - PLAYER.dirz * PLAYER.movespeed * 0.8 * 3))
			PLAYER.posz -= PLAYER.dirz * PLAYER.movespeed * 0.8;
	}

	if (IS_MOVING(KEY_D))
	{
		if (!COLLIDING_Z_AXIS(PLAYER.posz + PLAYER.dirx * -PLAYER.movespeed * 3))
			PLAYER.posz += PLAYER.dirx * -PLAYER.movespeed;
		if (!COLLIDING_X_AXIS(PLAYER.posx + PLAYER.dirz * PLAYER.movespeed * 3))
			PLAYER.posx += PLAYER.dirz * PLAYER.movespeed;
	}

	if (IS_MOVING(KEY_A))
	{
		if (!COLLIDING_Z_AXIS(PLAYER.posz - PLAYER.dirx * -PLAYER.movespeed * 3))
			PLAYER.posz -= PLAYER.dirx * -PLAYER.movespeed;
		if (!COLLIDING_X_AXIS(PLAYER.posx - PLAYER.dirz * PLAYER.movespeed * 3))
			PLAYER.posx -= PLAYER.dirz * PLAYER.movespeed;
	}

	if (IS_MOVING(KEY_SPACE) && PLAYER.posy == 0)
	{
		//jump
	}

	if (IS_MOVING(KEY_L_SHIFT) && PLAYER.posy == 0)
	{
		//crouch
	}

	if (IS_MOVING(KEY_W) || IS_MOVING(KEY_S) || IS_MOVING(KEY_A) || IS_MOVING(KEY_D))
	{
		if (current_milliseconds() - game->animation.walking_time >= 50L) {
			game->animation.walking += game->animation.walking >= 0 ? 1 : -1;

			if (game->animation.walking == 5)
				game->animation.walking = -1;
			else if (game->animation.walking == -5)
				game->animation.walking = 0;

			PLAYER.pitch += game->animation.walking;
			game->animation.walking_time = current_milliseconds();
		}
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