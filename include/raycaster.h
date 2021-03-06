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

#endif
