#include "cub3d.h"
#include "renderer.h"

int		run_render_battle(t_game *game)
{
	ft_glRecText(vector(0, 0), RESX, RESY, TXTRS.hud[0]);
	ft_glRectangle(vector(scale_w(235.0, RESX), scale_h(111.0, RESY)),
				(int)scale_w(256.0 / 100.0 * STORY.enemy_hp, RESX),
				(int)scale_h(14.0, RESY),
				hp_to_color(STORY.enemy_hp));
	ft_glRectangle(vector(scale_w(959.0, RESX), scale_h(383.0, RESY)),
				(int)scale_w(256.0 / 100.0 * STORY.own_hp, RESX),
				(int)scale_h(14.0, RESY),
				hp_to_color(STORY.own_hp));
	if (!STORY.catching)
		ft_glRecText(vector(RESX / 3. * 2., 10), RESY / 3, RESY / 3,
										BACKSPRITE[STORY.enemy_pkm]);
	else
		ft_glRecText(vector(RESX / 2. + 150, -100), RESY / 2, RESY / 2,
												TXTRS.environment[7]);
	if_catching(game);
	if (!STORY.alive && (current_milliseconds() - STORY.atk_time) > 2000L)
	{
		mlx_mouse_hide();
		game->gamestate = PLAYING;
	}
	if (STORY.alive && STORY.atk_turn == 1 &&
				(current_milliseconds() - STORY.atk_time) > 2000L)
		attack_player(game);
	return (TRUE);
}

int		if_catching(t_game *game)
{
	ft_glRecText(vector(RESX / 2. / 3., RESY / 3.), RESY / 3, RESY / 3,
										BACKSPRITE[STORY.own_pkm]);
	ft_glString(40, 52, PKM_DATA[STORY.enemy_pkm].name, TXTRS.fonts[0]);
	ft_glString(780, 322, PKM_DATA[STORY.own_pkm].name, TXTRS.fonts[0]);
	if (STORY.catching)
	{
		if ((current_milliseconds() - STORY.catching_time) > 2000L)
		{
			if (ft_irandom(0, 101 - STORY.enemy_hp) > 50)
			{
				STORY.squad[STORY.count++] = STORY.enemy_pkm;
				if (STORY.count >= 152)
					STORY.count = 0;
				STORY.catching = 0;
				mlx_mouse_hide();
				game->gamestate = PLAYING;
				return (TRUE);
			}
			STORY.catching = 0;
			STORY.atk_turn = 1;
			STORY.atk_time = current_milliseconds();
		}
		return (TRUE);
	}
	return (TRUE);
}

int		init_battle(t_game *game)
{
	STORY.enemy_hp = 100;
	STORY.own_hp = 100;
	STORY.own_pkm = STORY.squad[ft_irandom(0, STORY.count)];
	STORY.enemy_pkm = ft_irandom(0, game->settings.pokemon_count);
	STORY.atk_turn = 0;
	STORY.alive = 1;
	STORY.catching = 0;
	game->gamestate = FIGHTING;
	mlx_mouse_show();
	return (TRUE);
}

int		attack_opponent(t_game *game)
{
	STORY.enemy_hp -= ft_irandom(0, MAX(60, STORY.enemy_hp));
	STORY.alive = STORY.enemy_hp > 0;
	STORY.atk_turn = 1;
	STORY.atk_time = current_milliseconds();
	return (TRUE);
}

int		attack_player(t_game *game)
{
	STORY.own_hp -= ft_irandom(0, MAX(60, STORY.own_hp));
	STORY.alive = STORY.own_hp > 0;
	STORY.atk_turn = 0;
	STORY.atk_time = current_milliseconds();
	return (TRUE);
}
