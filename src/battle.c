#include "../headers/cub3d.h"
#include "../headers/renderer.h"
#include "../headers/battle.h"

/*
**	Norminette V3 Status: OK!
*/

int	ft_run_render_battle(t_game *game)
{
	ft_glRecText(vector(0, 0), RESX, RESY, TXTRS.hud[0]);
	ft_render_enemyhp(game);
	ft_render_ownhp(game);
	if (!STORY.catching)
		ft_glRecText(vector(RESX / 3. * 2., 10), RESY / 3, RESY / 3,
			FRONTSPRITE[STORY.enemy_pkm]);
	else
		ft_glRecText(vector(RESX / 2. + 150, -100), RESY / 2, RESY / 2,
			TXTRS.environment[7]);
	ft_glRecText(vector(RESX / 7., RESY / 5.), RESY / 2., RESY / 2.,
		BACKSPRITE[STORY.own_pkm]);
	ft_if_catching(game);
	if (!STORY.alive && (current_milliseconds() - STORY.atk_time) > 2000L)
	{
		mlx_mouse_hide();
		game->gamestate = PLAYING;
		playMusic("./resources/sounds/route42.wav", SDL_MIX_MAXVOLUME / 4);
	}
	if (STORY.alive && STORY.atk_turn == 1 && (current_milliseconds()
			- STORY.atk_time) > 2000L)
		attack_player(game);
	return (TRUE);
}

int	ft_if_catching(t_game *game)
{
	ft_glString(40, 52, PKM_DATA[STORY.enemy_pkm].name, TXTRS.fonts[0]);
	ft_glString(780, 322, PKM_DATA[STORY.own_pkm].name, TXTRS.fonts[0]);
	if (STORY.catching)
	{
		if ((current_milliseconds() - STORY.catching_time) > 5000L)
		{
			if (ft_irandom(0, 101 - STORY.enemy_hp) > 25)
			{
				playSound("./resources/sounds/pokemon_caught.wav", MAXVOL);
				STORY.squad[STORY.count++] = STORY.enemy_pkm;
				if (STORY.count >= 152)
					STORY.count = 0;
				STORY.catching = 0;
				mlx_mouse_hide();
				game->gamestate = PLAYING;
				playMusic("./resources/sounds/route42.wav", MAXVOL / 4);
				return (TRUE);
			}
			STORY.catching = 0;
			STORY.atk_turn = 1;
			STORY.atk_time = current_milliseconds();
		}
	}
	return (TRUE);
}

int	ft_init_battle(t_game *game)
{
	playMusic("./resources/sounds/battle.wav", SDL_MIX_MAXVOLUME / 8);
	STORY.enemy_hp = 100;
	STORY.own_hp = 100;
	STORY.own_pkm = STORY.squad[ft_irandom(0, STORY.count)];
	STORY.enemy_pkm = ft_irandom(0, game->settings.pokemon_count);
	STORY.atk_turn = 0;
	STORY.alive = 1;
	STORY.catching = 0;
	STORY.atk_time = 0;
	game->gamestate = FIGHTING;
	mlx_mouse_show();
	return (TRUE);
}

int	ft_attack_opponent(t_game *game)
{
	STORY.enemy_hp -= ft_irandom(0, MAX(60, STORY.enemy_hp));
	STORY.alive = STORY.enemy_hp > 0;
	STORY.atk_turn = 1;
	STORY.atk_time = current_milliseconds();
	playSound("./resources/sounds/attack.wav", SDL_MIX_MAXVOLUME);
	return (TRUE);
}

int	attack_player(t_game *game)
{
	STORY.own_hp -= ft_irandom(0, MAX(60, STORY.own_hp));
	STORY.alive = STORY.own_hp > 0;
	STORY.atk_turn = 0;
	STORY.atk_time = current_milliseconds();
	playSound("./resources/sounds/attack.wav", SDL_MIX_MAXVOLUME);
	return (TRUE);
}
