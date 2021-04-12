#include <stdio.h>
#include "include/parser.h"
#include "include/cub3d.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char*)(s1 + i) != *(unsigned char*)(s2 + i))
			return (*(unsigned char*)(s1 + i) - *(unsigned char*)(s2 + i));
		i++;
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
	if (argv[2] != 0)
	{
		if (!ft_memcmp(argv[2], "--save", ft_strlen(argv[2])))
			game.screenshot = TRUE;
		else
		{
			perror("Unknown argument it should be --save");
			return (1);
		}
	}
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
