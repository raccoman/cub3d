#ifndef CUB3D_H
#define CUB3D_H

# include "settings.h"
# include "texture.h"
# include "utils.h"
# include "keyboard.h"
# include <time.h>

typedef struct	s_manager
{
	void	*instance;
	void	*window;
	short	inputs[270];
}				t_manager;

typedef struct	s_timer
{
	int64_t	last_update;
	int64_t	elapsed_ticks;
}				t_timer;

typedef struct	s_player
{
	double	posx;
	double	posz;
	double	posy;
	double	dirx;
	double	dirz;
	double	planex;
	double	planez;
	int		pitch;
	int		yaw;
	double	movespeed;
	double	rotatespeed;
}				t_player;

typedef struct	s_animation
{
	int		walking;
	int64_t	walking_time;
}				t_animation;

typedef struct	s_sprite
{
	double	posx;
	double	posz;
	int		texture_id;
}				t_sprite;

typedef struct	s_game
{
	int	res_height;
	int	res_width;

	signed char 	**map;

	t_sprite		*sprites;
	int				sprite_count;

	t_textures		textures;
	t_settings		settings;
	t_animation		animation;
	t_player		player;
	t_timer			timer;
	t_manager		manager;
}				t_game;

int				onWindowClose(t_game *game);

int				onKeyPress(int key, t_game *game);

int				onKeyRelease(int key, t_game *game);

int				onMouseClick(int button, int x, int y, t_game *game);

int				onGameLoop(t_game *game);

int				init_game(t_game *game);

int				load_textures(t_game *game);

int				run_game(t_game *game);

int				run_tick(t_game *game);

int64_t			current_milliseconds();

void			update_timer(t_timer *timer);

void			init_player(t_settings settings, t_player *player, t_animation *animation);

int				run_player_tick(t_game *game);

int				rotate_player(t_game *game, double rotatespeed);

int				run_mouse_tick(t_game *game);

#endif
