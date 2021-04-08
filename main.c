#include <stdio.h>
#include "parser.h"
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game game;

	game.screenshot = FALSE;
	if (argc < 2 || argc > 3)
	{
		perror("Usage: ./cub3D <Settings File Path> [--save]");
		return (1);
	}
	if (argv[2] == "--save")
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
