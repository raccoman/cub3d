#include "cub3d.h"

void w_key(t_game *game)
{
	if (IS_MOVING(KEY_W))
	{
		if (!COLLIDING_X_AXIS(PLAYER.posx + PLAYER.dirx * PLAYER.movespeed * 3))
			PLAYER.posx += PLAYER.dirx * PLAYER.movespeed;
		if (!COLLIDING_Z_AXIS(PLAYER.posz + PLAYER.dirz * PLAYER.movespeed * 3))
			PLAYER.posz += PLAYER.dirz * PLAYER.movespeed;
	}
}

void s_key(t_game *game)
{
	if (IS_MOVING(KEY_S))
	{
		if (!COLLIDING_X_AXIS(PLAYER.posx - PLAYER.dirx * PLAYER.movespeed * 0.8 * 3))
			PLAYER.posx -= PLAYER.dirx * PLAYER.movespeed * 0.8;
		if (!COLLIDING_Z_AXIS(PLAYER.posz - PLAYER.dirz * PLAYER.movespeed * 0.8 * 3))
			PLAYER.posz -= PLAYER.dirz * PLAYER.movespeed * 0.8;
	}
}

void a_key(t_game *game)
{
	if (IS_MOVING(KEY_A))
	{
		if (!COLLIDING_Z_AXIS(PLAYER.posz - PLAYER.dirx * -PLAYER.movespeed * 3))
			PLAYER.posz -= PLAYER.dirx * -PLAYER.movespeed;
		if (!COLLIDING_X_AXIS(PLAYER.posx - PLAYER.dirz * PLAYER.movespeed * 3))
			PLAYER.posx -= PLAYER.dirz * PLAYER.movespeed;
	}
}

void d_key(t_game *game)
{
	if (IS_MOVING(KEY_D))
	{
		if (!COLLIDING_Z_AXIS(PLAYER.posz + PLAYER.dirx * -PLAYER.movespeed * 3))
			PLAYER.posz += PLAYER.dirx * -PLAYER.movespeed;
		if (!COLLIDING_X_AXIS(PLAYER.posx + PLAYER.dirz * PLAYER.movespeed * 3))
			PLAYER.posx += PLAYER.dirz * PLAYER.movespeed;
	}
}
