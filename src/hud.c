# include "cub3d.h"
# include "renderer.h"

int	run_render_hud(t_game *game)
{

	if (game->gamestate == PLAYING)
		if (game->story.pokeflaute)
			ft_glRecText(vector(game->res_width - 180, game->res_height - 160), 200, 200, game->textures.hud[1]);

	return (TRUE);
}