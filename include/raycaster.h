#ifndef RAYCASTER_H
#define RAYCASTER_H

# include "texture.h"

typedef struct	s_vraycasting
{
	int		x;
	int		y;
	double	camerax;
	double	dirx;
	double	dirz;
	int		mapx;
	int		mapz;
	double	sidedistx;
	double	sidedistz;
	double	deltadistx;
	double	deltadistz;
	double	perpwalldist;
	int		stepx;
	int		stepz;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wallx;
	int		texturex;
	int		texturey;
	double	step;
	double	text_pos;
	uint32_t		color;
	t_texture_data	texture;
}				t_vraycasting;

typedef struct	s_hraycasting
{
	int		x;
	int		y;
	double	dirx;
	double	dirz;
	double	dirx1;
	double	dirz1;
	int		p;
	double	posy;
	double	rowdistance;
	double	floorstepx;
	double	floorstepz;
	double	floorx;
	double	floorz;
	int		cellx;
	int		cellz;
	int		texturex;
	int		texturey;
	uint32_t		color;
	t_texture_data	texture;
}				t_hraycasting;

typedef struct	s_sraycasting
{
	int		i;
	double	spritex;
	double	spritez;
	double	invdet;
	double	transformx;
	double	transformz;
	int		vmovescreen;
	int		spritescreenx;
	int		spriteheight;
	int		drawstartz;
	int		drawendz;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;
	int		stripe;
	int		d;
	int		z;
	int		texturex;
	int		texturey;
	double	ybuffer[5120];
	uint32_t		color;
	t_texture_data	texture;
}				t_sraycasting;

void			ft_hraycast(t_hraycasting *hraycasting, t_game *game);
void			ft_vraycast(t_game *game, t_vraycasting *vraycasting, t_sraycasting *sraycasting);

#endif
