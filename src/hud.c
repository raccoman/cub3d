# include "cub3d.h"
# include "renderer.h"

int				run_render_hud(t_game *game)
{

	if (game->gamestate == PLAYING)
	{

		if (game->story.mn_cut)
		{
			ft_glRectangleTextured(new_vector(game->res_width - 160, game->res_height - 160), 200, 200, game->textures.hud[1]);
		}

	}

	return (TRUE);
}