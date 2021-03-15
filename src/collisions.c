# include "cub3d.h"

int	is_colliding(t_game *game, int x, int z)
{
	int i;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].present && x == (int)game->sprites[i].posx && z == (int)game->sprites[i].posz) {
			onCollideSprite(game, &game->sprites[i]);
			return (TRUE);
		}
		i++;
	}

    if (game->map[x][z] != '0')
    {
        onCollideWall(game, x, z);
        return (TRUE);
    }

	return (FALSE);
}