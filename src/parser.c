#include <printf.h>
# include "parser.h"

int	parse_resolution(t_game *game, char *string)
{
	char *reading;

	if(!(reading = ft_skip_charset(string, "R \t"))) //Unsafe should simplify this one
		return (FALSE);
	game->res_w = ft_clamp(5120, 640, ft_atoi(&reading));
	game->res_h = ft_clamp(2880, 360, ft_atoi(&reading));
	free(string);
	return (TRUE);
}

int	parse_texture(t_game *game, char *string, t_texture_path texture)
{
	char *path;

	if(!(path = ft_skip_charset(string, "ABCDEFGHKIJKLMNOPQRSTUVWXYZ_ \t\r"))) //Unsafe should simplify this one
		return (FALSE);
	game->settings.env_texture_path[texture] = ft_strdup(path);
	free(string);
	return (TRUE);
}

int	parse_pokemon(t_game *game, char *string)
{
	char *reading;
	char *name;
	char *file_name;

	reading = ft_starts_with(string, "POKEMON");
	reading = ft_skip_charset(reading, " \t\r");
	name = reading;
	reading = ft_skip_charset(reading, "ABCDEFGHKIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	reading = ft_skip_charset(reading, " \t\r");
	file_name = reading;

	game->settings.pkm_data[game->settings.pokemon_count].name = ft_terminate_at(ft_strdup(name), " \t\r");
	game->settings.pkm_data[game->settings.pokemon_count].back_path = ft_concatenate("./resources/texture/pokemon/back/", file_name);
	game->settings.pkm_data[game->settings.pokemon_count].front_path = ft_concatenate("./resources/texture/pokemon/front/", file_name);
	game->settings.pokemon_count++;

	free(string);
	return (TRUE);
}

int	parse_map(t_game *game, char *string)
{
	int			i;
	int			k;
	static int	size = 0;
	signed char	**new_map;
	int			spawn;
	t_sprite	*new_sprites;
	int			sprite;

	size++;
	if (!(new_map = malloc(sizeof(signed char *) * (size + 1))))
		return (FALSE);
	i = 0;
	while (i < size - 1)
	{
		new_map[i] = game->map[i];
		i++;
	}
	if ((spawn = ft_find(string, "NSWE")) >= 0)
	{
		if (game->settings.spawn.x != -1)
			return (FALSE);

		game->settings.spawn = vector(i, spawn);
		if (string[spawn] == 'N')
			game->settings.direction = NORTH;
		else if (string[spawn] == 'S')
			game->settings.direction = SOUTH;
		else if (string[spawn] == 'W')
			game->settings.direction = WEST;
		else if (string[spawn] == 'E')
			game->settings.direction = EAST;
		string[spawn] = '0';
	}
	while ((sprite = ft_find(string, "234")) >= 0)
	{
		game->sprite_count++;
		if (!(new_sprites = malloc(sizeof(t_sprite) * (game->sprite_count + 1))))
			return (FALSE);
		k = 0;
		while (k < (game->sprite_count - 1))
		{
			new_sprites[k] = game->sprites[k];
			k++;
		}
		new_sprites[k].present = 1;
		new_sprites[k].posx = i + 0.5;
		new_sprites[k].posz = sprite + 0.5;

		if (string[sprite] == '2')
			new_sprites[k].texture_id = 6;
		else if (string[sprite] == '3')
			new_sprites[k].texture_id = 7;
		else if (string[sprite] == '4')
			new_sprites[k].texture_id = 8;
		free(game->sprites);
		game->sprites = new_sprites;
		string[sprite] = '0';
	}
	new_map[i] = (signed char *)ft_strdup(string);
	new_map[i + 1] = NULL;
	free(game->map);
	game->map = new_map;
	free(string);
	return (TRUE);
}

int	parse_settings(t_game *game, const char *path)
{
	int		fd;
	char	*line;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (FALSE);
	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "R") || !parse_resolution(game, line))
			return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "NO") || !parse_texture(game, line, NO_TEXTURE_PATH))
		return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "SO") || !parse_texture(game, line, SO_TEXTURE_PATH))
		return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "WE") || !parse_texture(game, line, WE_TEXTURE_PATH))
		return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "EA") || !parse_texture(game, line, EA_TEXTURE_PATH))
		return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "F") || !parse_texture(game, line, F_TEXTURE_PATH))
		return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "C") || !parse_texture(game, line, C_TEXTURE_PATH))
		return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "S_BUSH") || !parse_texture(game, line, S_BUSH_TEXTURE_PATH))
		return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "S_MASTERBALL") || !parse_texture(game, line, S_MASTERBALL_TEXTURE_PATH))
		return (FALSE);

	if (gnnel(fd, &line) < 0 || !ft_starts_with(line, "S_SNORLAX") || !parse_texture(game, line, S_SNORLAX_TEXTURE_PATH))
		return (FALSE);

	game->settings.pokemon_count = 0;
	while (gnnel(fd, &line) >= 0 && ft_starts_with(line, "POKEMON"))
		parse_pokemon(game, line);

	game->map = NULL;
	game->sprites = NULL;
	game->sprite_count = 0;
	game->settings.spawn = vector(-1, -1);

	if (!ft_contains_only(line,"01234NSWE ") || !parse_map(game, line))
		return (FALSE);
	while (gnl(fd, &line) > 0)
	{
		if (!ft_contains_only(line,"01234NSWE ") || !parse_map(game, line))
			return (FALSE);
	}
	if (!ft_contains_only(line,"01234NSWE ") || !parse_map(game, line))
		return (FALSE);

	/*
	printf("Resolution: %dx%d\n", game->res_w, game->res_h);
	for (int i = 0; i < 8; ++i)
		printf("Texture #%d: [%s]\n", i, game->settings.env_texture_path[i]);
	for (int i = 0; i < game->settings.pokemon_count; ++i)
		printf("Pokemon #%d: %s %s %s\n", i, game->settings.pkm_data[i].name, game->settings.pkm_data[i].front_path, game->settings.pkm_data[i].back_path);
	 for (int i = 0; game->map[i] != NULL ; ++i) {
		printf("%s\n", game->map[i]);
	}
	 printf("Spawn: %f %f %d", game->settings.spawn.x, game->settings.spawn.z, game->settings.direction);*/
	return (TRUE);
}