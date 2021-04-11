#ifndef MYDEF_H
# define MYDEF_H

/*
**	battle.c
*/

# define RESX game->res_w
# define RESY game->res_h
# define TXTRS game->textures
# define STORY game->story
# define PKM_DATA game->settings.pkm_data
# define BACKSPRITE game->textures.backsprite
# define FRONTSPRITE game->textures.frontsprite

/*
** player.c
*/

#define PLAYER game->player
#define IS_MOVING(x) game->manager.inputs[x]
#define COLLIDING_X_AXIS(x) is_colliding(game, (int)(x), (int)PLAYER.posz)
#define COLLIDING_Z_AXIS(z) is_colliding(game, (int)PLAYER.posx, (int)(z))

/*
**  world.c
*/

#define PLAYER game->player

#endif
