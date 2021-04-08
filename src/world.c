#include "cub3d.h"
#include "renderer.h"
#include "raycaster.h"
#include "screenshot.h"


int				run_render_tick(t_game *game)
{
	t_hraycasting	hraycasting;
	t_vraycasting	vraycasting;
	t_sraycasting	sraycasting;

	ft_glSkyBox(game->player.yaw, game->player.pitch, game->res_width, game->res_height, game->textures.environment[5]);

	ft_hraycast(&hraycasting, game);
	ft_vraycast(game, &vraycasting, &sraycasting);
	sraycasting.i = 0;
	while (sraycasting.i < game->sprite_count)
	{
		if (!game->sprites[sraycasting.i].present)
		{
			sraycasting.i++;
			continue;
		}
		sraycasting.spritex = game->sprites[sraycasting.i].posx - PLAYER.posx;
		sraycasting.spritez = game->sprites[sraycasting.i].posz - PLAYER.posz;

		sraycasting.invdet = 1.0 / (PLAYER.planex * PLAYER.dirz - PLAYER.dirx * PLAYER.planez);

		sraycasting.transformx = sraycasting.invdet * (PLAYER.dirz * sraycasting.spritex - PLAYER.dirx * sraycasting.spritez);
		sraycasting.transformz = sraycasting.invdet * (-PLAYER.planez * sraycasting.spritex + PLAYER.planex * sraycasting.spritez);

		sraycasting.vmovescreen = PLAYER.pitch;
		sraycasting.spritescreenx = (int)((game->res_width / 2.0) * (1 + sraycasting.transformx / sraycasting.transformz));

		sraycasting.spriteheight = abs((int) (game->res_height / sraycasting.transformz));

		sraycasting.drawstartz = ft_max(0, -sraycasting.spriteheight / 2 + game->res_height / 2 + sraycasting.vmovescreen);
		sraycasting.drawendz = ft_min(game->res_height - 1, sraycasting.spriteheight / 2 + game->res_height / 2 + sraycasting.vmovescreen);

		sraycasting.spritewidth = abs((int) (game->res_height / sraycasting.transformz));

		sraycasting.drawstartx = ft_max(0, -sraycasting.spritewidth / 2 + sraycasting.spritescreenx);
		sraycasting.drawendx = ft_min(game->res_width - 1, sraycasting.spritewidth / 2 + sraycasting.spritescreenx);

		sraycasting.texture = game->textures.environment[game->sprites[sraycasting.i].texture_id];

		sraycasting.stripe = sraycasting.drawstartx;
		while (sraycasting.stripe < sraycasting.drawendx)
		{
			sraycasting.texturex = (int)(256 * (sraycasting.stripe - (-sraycasting.spritewidth / 2 + sraycasting.spritescreenx)) * sraycasting.texture.width / sraycasting.spritewidth) / 256;
			if (sraycasting.transformz > 0 && sraycasting.transformz < sraycasting.ybuffer[sraycasting.stripe])
			{
				sraycasting.z = sraycasting.drawstartz;
				while (sraycasting.z < sraycasting.drawendz)
				{
					sraycasting.d = (sraycasting.z - sraycasting.vmovescreen) * 256 - game->res_height * 128 + sraycasting.spriteheight * 128;
					sraycasting.texturey = sraycasting.d * sraycasting.texture.height / sraycasting.spriteheight / 256;

					sraycasting.color = ((unsigned int *)sraycasting.texture.address)[sraycasting.texture.width * sraycasting.texturey + sraycasting.texturex];
					ft_glPixel(sraycasting.stripe, sraycasting.z, sraycasting.color);

					sraycasting.z++;
				}
			}
			sraycasting.stripe++;
		}

		sraycasting.i++;
	}

	if (1)
		{
				ft_screenshot(&data, game);
				exit(1);
		}

	return (TRUE);
}

int				run_tick(t_game *game)
{
	int i;

	ft_glClear(game->manager.instance, game->manager.window);
	ft_glBegin(game->manager.instance, game->res_width, game->res_height, 0x00FF00);

	if (game->story.pokeflaute_time && current_milliseconds() - game->story.pokeflaute_time > 20000L)
	{
		i = 0;
		while (i < game->sprite_count)
		{
			if (game->sprites[i].texture_id == 8) {
				game->sprites->present = 0;
				break;
			}
		}
		playMusic("../resources/sounds/route42.wav", SDL_MIX_MAXVOLUME / 4);
		game->story.pokeflaute_time = 0;
	}

	if (game->gamestate == PLAYING)
	{
		if (!run_mouse_tick(game))
			return (FALSE);
	}

	if (game->gamestate == PLAYING)
	{
		if (!run_player_tick(game))
			return (FALSE);
	}

	if (game->gamestate == PLAYING)
	{
		if (!run_render_tick(game))
			return (FALSE);
	}

	if (game->gamestate == FIGHTING)
	{
		if (!run_render_battle(game))
			return (FALSE);
	}

	if (game->gamestate == PLAYING || game->gamestate == PAUSE)
	{
		if (!run_render_hud(game))
			return (FALSE);
	}

	ft_glEnd(game->manager.instance, game->manager.window, 0, 0);
	return (TRUE);
}
