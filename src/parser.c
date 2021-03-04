# include "parser.h"

int	parse_resolution(t_game *game, int fd)
{
	char	*line;
	char	*slider;

	while (gnl(fd, &line) > 0)
	{
		slider = line;
		if (*(slider = skip_isspace(slider)) != 0)
			break;
		free(line);
	}
	if (*slider != 'R')
		return (FALSE);
	skip_isspace(++slider);
	game->res_width = ft_clamp(ft_atoi(&slider), 2560, 640);
	game->res_height = ft_clamp(ft_atoi(&slider), 1440, 360);
	free(line);
	return (TRUE);
}

int	parse_textures(t_game *game, int fd)
{

	return (TRUE);
}

int	parse_pokemon(t_game *game, int fd)
{
	return (TRUE);
}

int	parse_map(t_game *game, int fd)
{
	return (TRUE);
}

int	parse_settings(t_game *game, const char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (FALSE);

	if (!parse_resolution(game, fd))
		return (FALSE);

	if (!parse_textures(game, fd))
		return (FALSE);

	if (!parse_pokemon(game, fd))
		return (FALSE);

	if (!parse_map(game, fd))
		return (FALSE);

	return (TRUE);
}