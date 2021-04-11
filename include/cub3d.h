#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include "settings.h"
# include "utils.h"
# include "keyboard.h"
# include <time.h>
# include "mydef.h"
# include "sound.h"

# define KEY_PRESSED(x) game->manager.inputs[x]

typedef enum	e_gamestate
{
	PLAYING,
	FIGHTING,
	PAUSE
}				t_gamestate;

typedef struct	s_texture_data
{
	void	*image;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_texture_data;

typedef struct	s_textures
{
	t_texture_data fonts[1];
	t_texture_data hud[2];
	t_texture_data environment[9];
	t_texture_data frontsprite[152];
	t_texture_data backsprite[152];
}				t_textures;

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
	int64_t	footstep_time;
}				t_animation;

typedef struct	s_sprite
{
	double	posx;
	double	posz;
	int		present;
	int		texture_id;
}				t_sprite;

typedef struct	s_story
{
	int	pokeflaute;
	int squad[152];
	int count;
	int	enemy_hp;
	int	own_hp;
	int	enemy_pkm;
	int	own_pkm;
	int	atk_turn;
	int	alive;
	int64_t	atk_time;
	int catching;
	int64_t catching_time;
	int64_t pokeflaute_time;

}				t_story;

typedef struct	s_game
{
	int				res_h;
	int				res_w;
	int				screenshot;
	signed char 	**map;
	t_sprite		*sprites;
	int				sprite_count;
	t_gamestate		gamestate;
	t_story			story;
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

int				ft_onmouse_click(int button, int x, int y, t_game *game);

int				onGameLoop(t_game *game);

int				onCollideSprite(t_game *game, t_sprite *sprite);

int				init_game(t_game *game);

int				load_textures(t_game *game);

int				run_game(t_game *game);

int				run_tick(t_game *game);

int64_t			current_milliseconds();

void			update_timer(t_timer *timer);

void			init_player(t_settings settings, t_player *player, t_animation *anim);

int				run_player_tick(t_game *game);

int				rotate_player(t_game *game, double rotatespeed);

int				run_mouse_tick(t_game *game);

int				is_colliding(t_game *game, int x, int z);

int				init_story(t_game *game);




int				run_render_hud(t_game *game);



int				end_game(t_game *game);

#endif
