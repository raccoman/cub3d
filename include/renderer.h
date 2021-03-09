#ifndef RENDERER_H
#define RENDERER_H

# include <stdlib.h>
# include "mlx.h"
# include "utils.h"
# include "texture.h"

typedef struct	s_data
{
	uint32_t	mask;
	void		*image;
	char		*address;
	int			bpp;
	int			line_length;
	int			endian;
}				t_data;

t_data	data;

uint32_t		ft_rgba(int red, int green, int blue, int alpha);

uint32_t		ft_rgb(int red, int green, int blue);

void			ft_glClear(void *instance, void *window);

void			ft_glBegin(void *instance, int width, int height, int mask);

void			ft_glEnd(void *instance, void *window, int x, int y);

uint32_t		ft_glGetPixelColor(int x, int y, t_texture_data texture);

void			ft_glPixel(int x, int y, uint32_t color);

void			ft_glRectangle(t_vector origin, int width, int height, int color);

void			ft_glRoundedRectangle(t_vector origin, int radius, int width, int height, int color);

void			ft_glRectangleTextured(t_vector origin, int width, int height, t_texture_data texture);

void			ft_glCircle(t_vector origin, int radius, int color);

void			ft_glFilledCircle(t_vector origin, int radius, int color);

void			ft_glSkyBox(int offsetx, int offsety, int res_width, int res_height, t_texture_data texture);

double			ft_scale_by_width(double v, int width);

double			ft_scale_by_height(double v, int height);

#endif
