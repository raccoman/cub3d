#include <stdio.h>
#include "parser.h"
#include "cub3d.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && *(unsigned char*)(s1 + i) && *(unsigned char*)(s2 + i))
	{
		if (*(unsigned char*)(s1 + i) == *(unsigned char*)(s2 + i))
			i++;
		else
		{
			if (*(unsigned char*)(s1 + i) > *(unsigned char*)(s2 + i))
				return (1);
			else
				return (-1);
		}
	}
	if (i == n)
		return (0);
	else
	{
		if (*(unsigned char*)(s1 + i) > *(unsigned char*)(s2 + i))
			return (1);
		if (*(unsigned char*)(s1 + i) < *(unsigned char*)(s2 + i))
			return (-1);
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_game game;

	game.screenshot = FALSE;
	if (argc < 2 || argc > 3)
	{
		perror("Usage: ./cub3D <Settings File Path> [--save]");
		return (1);
	}
	if (!ft_strncmp(argv[2], "--save", 6))
		game.screenshot = TRUE;
	if (!parse_settings(&game, argv[1]))
	{
		perror("Unable to read settings. Error");
		return (1);
	}
	if (!init_game(&game))
	{
		perror("Unable to initialize game engine.");
		return (1);
	}
	if (!load_textures(&game)) {
		perror("Unable to load texture.");
		return (1);
	}
	if (!run_game(&game))
	{
		perror("Cub3D crashed unexpectedly.");
		return (1);
	}
	return (0);
}
