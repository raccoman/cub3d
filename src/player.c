#include "cub3d.h"
#include "key.h"

void		init_playerdir(t_player *player, t_vector dir, t_vector plane)
{
	player->dirx = dir.x;
	player->dirz = dir.z;
	player->planex = plane.x;
	player->planez = plane.z;
}

void		init_player(t_settings opt, t_player *player, t_animation *anim)
{
	player->posx = opt.spawn.x;
	player->posz = opt.spawn.z;
	player->posy = 0;
	if (opt.direction == NORTH)
		init_playerdir(player, vector(-1, 0), vector(0, 0.66));
	else if (opt.direction == SOUTH)
		init_playerdir(player, vector(1, 0), vector(0, -0.66));
	else if (opt.direction == WEST)
		init_playerdir(player, vector(0, -1), vector(-0.66, 0));
	else if (opt.direction == EAST)
		init_playerdir(player, vector(0, 1), vector(0.66, 0));
	player->rotatespeed = 0.1;
	player->movespeed = 0.1;
	anim->walking = 0;
	anim->walking_time = current_milliseconds();
}

int			run_player_tick(t_game *game)
{
	w_key(game);
	s_key(game);
	d_key(game);
	a_key(game);
	if (IS_MOVING(KEY_W) || IS_MOVING(KEY_S) || IS_MOVING(KEY_A) || IS_MOVING(KEY_D))
	{
		if (current_milliseconds() - game->animation.footstep_time > 450L)
		{
			playSound("../resources/sounds/footsteps.wav", SDL_MIX_MAXVOLUME);
			game->animation.footstep_time = current_milliseconds();
		}
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

int			rotate_player(t_game *game, double rotatespeed)
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
