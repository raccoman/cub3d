# include "cub3d.h"
# include "renderer.h"

int64_t	hp_to_color(int hp)
{
	if (hp >= 50)
		return 0x2CC91E;
	else if (hp >= 20)
		return 0xF2BA35;
	else
		return 0xAD271D;
}

int		run_render_battle(t_game *game)
{
	ft_glRectangleTextured(new_vector(0, 0), game->res_width, game->res_height, game->textures.hud[0]);

	ft_glRectangle(new_vector(ft_scale_by_width(235.0, game->res_width), ft_scale_by_height(111.0, game->res_height)),
				(int)ft_scale_by_width(256.0 / 100.0 * game->story.opponent_hp, game->res_width),
				(int)ft_scale_by_height(14.0, game->res_height),
				hp_to_color(game->story.opponent_hp));

	ft_glRectangle(new_vector(ft_scale_by_width(959.0, game->res_width), ft_scale_by_height(383.0, game->res_height)),
				(int)ft_scale_by_width(256.0 / 100.0 * game->story.own_hp, game->res_width),
				(int)ft_scale_by_height(14.0, game->res_height),
				hp_to_color(game->story.own_hp));

	ft_glRectangleTextured(new_vector(game->res_width / 3. * 2., 10),
						game->res_height / 3,game->res_height / 3,
						game->textures.closeup_pokemon[game->story.opponent_pokemon]);

	ft_glRectangleTextured(new_vector(game->res_width / 2. / 3., game->res_height / 3.),
						game->res_height / 3,game->res_height / 3,
						game->textures.closeup_pokemon[game->story.own_pokemon]);

	ft_glString(40, 52, game->settings.pokemon_data[game->story.opponent_pokemon].name, game->textures.fonts[0]);
	ft_glString(780, 322, game->settings.pokemon_data[game->story.own_pokemon].name, game->textures.fonts[0]);

	return (TRUE);
}

int				init_battle(t_game *game)
{
	game->story.opponent_hp = 100;
	game->story.own_hp = 100;
	game->story.own_pokemon = ft_irandom(0, game->settings.pokemon_count);
	game->story.opponent_pokemon = ft_irandom(0, game->settings.pokemon_count);

	game->gamestate = FIGHTING;
	mlx_mouse_show();
	return (TRUE);
}