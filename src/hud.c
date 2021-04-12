#include "../headers/cub3d.h"
#include "../headers/renderer.h"

/*
**	Norminette V3 Status: OK!
*/

int	run_render_hud(t_game *game)
{
	if (game->gamestate == PLAYING)
		if (game->story.pokeflaute)
			ft_glRecText(vector(game->res_w - 180, game->res_h - 160),
				200, 200, game->textures.hud[1]);
	return (TRUE);
}
