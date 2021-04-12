//
// Created by Roberto Boldini on 11/04/21.
//

#include "../headers/cub3d.h"
#include "../headers/renderer.h"

/*
**	Norminette V3 Status: OK!
*/

void	ft_render_enemyhp(t_game *game)
{
	ft_glRectangle(vector(scale_w(235.0, RESX), scale_h(111.0, RESY)),
		(int)scale_w(256.0 / 100.0 * STORY.enemy_hp, RESX),
		(int)scale_h(14.0, RESY),
		hp_to_color(STORY.enemy_hp));
}

void	ft_render_ownhp(t_game *game)
{
	ft_glRectangle(vector(scale_w(959.0, RESX), scale_h(383.0, RESY)),
		(int)scale_w(256.0 / 100.0 * STORY.own_hp, RESX),
		(int)scale_h(14.0, RESY),
		hp_to_color(STORY.own_hp));
}
