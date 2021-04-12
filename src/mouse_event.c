//
// Created by Roberto Boldini on 11/04/21.
//

#include "../headers/cub3d.h"
#include "../headers/battle.h"

/*
**	Norminette V3 Status: OK!
*/

/*
**			//Click RUN button line: 38
**
**	if (x >= game->res_w / 2 + game->res_w / 2 / 2
**	[3 * game->res_w / 4]
**	&& x <= game->res_w
**	&& y >= game->res_h / 3 * 2 + game->res_h / 3 / 2
**	[]
**	&& y <= game->res_h)
**
**			//Click catch button line: 55
**			//Click fight button line: 66
**
**	Debug:
**			printf("Key pressed: %d Position: %d %d\n", button, x, y);
**			line: 77
*/

void	ft_clickrun(t_game *game, int x, int y)
{
	if (x >= 3 * game->res_w / 4 && x <= game->res_w
		&& y >= 5 * game->res_h / 6 && y <= game->res_h)
	{
		mlx_mouse_hide();
		game->gamestate = PLAYING;
		playMusic("./resources/sounds/route42.wav", MAXVOL / 4);
	}
}

void	ft_clickcatch(t_game *game, int x, int y)
{
	if (x >= game->res_w / 2 && x <= 3 * game->res_w / 4
		&& y >= 5 * game->res_h / 6 && y <= game->res_h)
	{
		if (game->story.alive && game->story.atk_turn == 0
			&& (current_milliseconds() - game->story.atk_time) > 2000L)
		{
			playSound("./resources/sounds/pokemon_wiggle.wav", MAXVOL * 4);
			game->story.catching = 1;
			game->story.catching_time = current_milliseconds();
		}
	}
}

void	ft_clickattack(t_game *game, int x, int y)
{
	if (x >= game->res_w / 2 && x <= 3 * game->res_w / 4
		&& y >= 2 * game->res_h / 3 && y <= 5 * game->res_h / 6)
	{
		if (game->story.alive && game->story.atk_turn == 0
			&& (current_milliseconds() - game->story.atk_time) > 2000L)
			ft_attack_opponent(game);
	}
}

int	ft_onmouse_click(int button, int x, int y, t_game *game)
{
	if (game->gamestate == FIGHTING)
	{
		button = 1 * button;
		ft_clickrun(game, x, y);
		ft_clickcatch(game, x, y);
		ft_clickattack(game, x, y);
	}
	return (1);
}
