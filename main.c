#include <stdio.h>
#include "parser.h"
#include "texture.h"
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game game;

	if (argc < 2)
	{
		perror("Usage: ./cub3D <settings> [--save]");
		return (1);
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
	}/*
	if (!run_game(&game))
	{
		perror("Cub3D crashed unexpectedly.");
		return (1);
	}*/
	return (0);
}
