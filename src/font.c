# include "renderer.h"

void	ft_glString(int x, int y, const char *string, t_texture_data texture)
{
	int	i;
	int	dx;
	int	dy;
	int	fx;
	int	fy;
	int	width;
	int	height;
	int	c;
	int	max;


	width = texture.width / 8;
	height = texture.height / 12;
	i = 0;
	dx = x;
	max = 0;
	while (string[i])
	{
		c = (string[i] - '!');
		fx = (c % 8) * width;
		while (fx < (c % 8) * width + width)
		{
			dy = y;
			fy = c / 8 * height;
			while (fy < c / 8 * height + height)
			{
				uint32_t color = ft_glGetPixelColor(fx, fy, texture);
				ft_glPixel(dx, dy, color);
				if (color != 0x00FF00 && max < dx)
					max = dx;
				dy++;
				fy++;
			}
			dx++;
			fx++;
		}
		dx -= dx - max;
		i++;
	}
}