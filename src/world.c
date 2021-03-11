# include "cub3d.h"
# include "renderer.h"
# include "raycaster.h"

#define PLAYER game->player

int				run_render_tick(t_game *game)
{
	t_hraycasting	hraycasting;
	t_vraycasting	vraycasting;
	t_sraycasting	sraycasting;

	ft_glSkyBox(game->player.yaw, game->player.pitch, game->res_width, game->res_height, game->textures.environment[5]);

	hraycasting.texture = game->textures.environment[4];
	hraycasting.y = game->res_height / 2 + PLAYER.pitch;
	while (hraycasting.y < game->res_height)
	{
		hraycasting.dirx = PLAYER.dirx - PLAYER.planex;
		hraycasting.dirz = PLAYER.dirz - PLAYER.planez;
		hraycasting.dirx1 = PLAYER.dirx + PLAYER.planex;
		hraycasting.dirz1 = PLAYER.dirz + PLAYER.planez;

		hraycasting.p = hraycasting.y - game->res_height / 2 - PLAYER.pitch;
		hraycasting.posy = game->res_height / 2.0;
		hraycasting.rowdistance = hraycasting.posy / hraycasting.p;

		hraycasting.floorstepx = hraycasting.rowdistance * (hraycasting.dirx1 - hraycasting.dirx) / game->res_width;
		hraycasting.floorstepz = hraycasting.rowdistance * (hraycasting.dirz1 - hraycasting.dirz) / game->res_width;

		hraycasting.floorx = PLAYER.posx + hraycasting.rowdistance * hraycasting.dirx;
		hraycasting.floorz = PLAYER.posz + hraycasting.rowdistance * hraycasting.dirz;

		hraycasting.x = 0;
		while (hraycasting.x < game->res_width)
		{
			hraycasting.cellx = (int)hraycasting.floorx;
			hraycasting.cellz = (int)hraycasting.floorz;

			hraycasting.texturex = (int)(hraycasting.texture.width * (hraycasting.floorx - hraycasting.cellx)) & (hraycasting.texture.width - 1);
			hraycasting.texturey = (int)(hraycasting.texture.height * (hraycasting.floorz - hraycasting.cellz)) & (hraycasting.texture.height - 1);

			hraycasting.floorx += hraycasting.floorstepx;
			hraycasting.floorz += hraycasting.floorstepz;

			hraycasting.color = ((unsigned int *)hraycasting.texture.address)[hraycasting.texture.width * hraycasting.texturey + hraycasting.texturex];
			hraycasting.color = (hraycasting.color >> 1) & 8355711;

			ft_glPixel(hraycasting.x, hraycasting.y, hraycasting.color);

			hraycasting.x++;
		}

		hraycasting.y++;
	}

	vraycasting.texture = game->textures.environment[0]; //Change to add NO(0) SO(1) WE(2) EA(3)
	vraycasting.x = 0;
	while (vraycasting.x < game->res_width)
	{
		vraycasting.camerax = 2 * vraycasting.x / (double)game->res_width - 1;
		vraycasting.dirx = PLAYER.dirx + PLAYER.planex * vraycasting.camerax;
		vraycasting.dirz = PLAYER.dirz + PLAYER.planez * vraycasting.camerax;

		vraycasting.mapx = PLAYER.posx;
		vraycasting.mapz = PLAYER.posz;

		vraycasting.deltadistx = fabs(1 / vraycasting.dirx);
		vraycasting.deltadistz = fabs(1 / vraycasting.dirz);

		if (vraycasting.dirx < 0)
		{
			vraycasting.stepx = -1;
			vraycasting.sidedistx = (PLAYER.posx - vraycasting.mapx) * vraycasting.deltadistx;
		}
		else
		{
			vraycasting.stepx = 1;
			vraycasting.sidedistx = (vraycasting.mapx + 1 - PLAYER.posx) * vraycasting.deltadistx;
		}
		if (vraycasting.dirz < 0)
		{
			vraycasting.stepz = -1;
			vraycasting.sidedistz = (PLAYER.posz - vraycasting.mapz) * vraycasting.deltadistz;
		}
		else
		{
			vraycasting.stepz = 1;
			vraycasting.sidedistz = (vraycasting.mapz + 1 - PLAYER.posz) * vraycasting.deltadistz;
		}
		vraycasting.hit = 0;
		while (vraycasting.hit == 0)
		{
			if (vraycasting.sidedistx < vraycasting.sidedistz)
			{
				vraycasting.sidedistx += vraycasting.deltadistx;
				vraycasting.mapx += vraycasting.stepx;
				vraycasting.side = 0;
			}
			else
			{
				vraycasting.sidedistz += vraycasting.deltadistz;
				vraycasting.mapz += vraycasting.stepz;
				vraycasting.side = 1;
			}
			if (game->map[vraycasting.mapx][vraycasting.mapz] == '1')
			{
				vraycasting.hit = 1;
			}
		}

		if (vraycasting.side == 0)
			vraycasting.perpwalldist = (vraycasting.mapx - PLAYER.posx + (1.0 - vraycasting.stepx) / 2) / vraycasting.dirx;
		else
			vraycasting.perpwalldist = (vraycasting.mapz - PLAYER.posz + (1.0 - vraycasting.stepz) / 2) / vraycasting.dirz;

		vraycasting.line_height = (int)(game->res_height / vraycasting.perpwalldist);

		vraycasting.draw_start = (int)(-vraycasting.line_height * 1.4 + (double)game->res_height / 2 + PLAYER.pitch);
		if(vraycasting.draw_start < 0)
			vraycasting.draw_start = 0;

		vraycasting.draw_end = vraycasting.line_height / 2 + game->res_height / 2 + PLAYER.pitch;
		if (vraycasting.draw_end > game->res_height)
			vraycasting.draw_end = game->res_height;

		if (vraycasting.side == 0)
			vraycasting.wallx = PLAYER.posz + vraycasting.perpwalldist * vraycasting.dirz;
		else
			vraycasting.wallx = PLAYER.posx + vraycasting.perpwalldist * vraycasting.dirx;

		vraycasting.wallx -= floor(vraycasting.wallx);

		vraycasting.texturex = (int)(vraycasting.wallx * (double)vraycasting.texture.width);

		if ((vraycasting.side == 0 && vraycasting.dirx > 0) || (vraycasting.side == 1 && vraycasting.dirz < 0))
			vraycasting.texturex = vraycasting.texture.width - vraycasting.texturex - 1;

		vraycasting.step = (double)vraycasting.texture.height / (double)vraycasting.line_height * .5;
		vraycasting.text_pos = (vraycasting.draw_start - (int)PLAYER.pitch - game->res_height / 2.0 + vraycasting.line_height * 1.5) * vraycasting.step;

		vraycasting.y = vraycasting.draw_start;
		while (vraycasting.y < vraycasting.draw_end)
		{
			vraycasting.texturey = (int)vraycasting.text_pos & (vraycasting.texture.height - 1);
			vraycasting.text_pos += vraycasting.step;

			vraycasting.color = ((unsigned int *)vraycasting.texture.address)[vraycasting.texture.height * vraycasting.texturey + vraycasting.texturex];
			ft_glPixel(vraycasting.x, vraycasting.y, vraycasting.color);
			vraycasting.y++;
		}
		sraycasting.ybuffer[vraycasting.x] = vraycasting.perpwalldist;
		vraycasting.x++;
	}

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

	return (TRUE);
}

int				run_tick(t_game *game)
{
	ft_glClear(game->manager.instance, game->manager.window);
	ft_glBegin(game->manager.instance, game->res_width, game->res_height, 0x00FF00);

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