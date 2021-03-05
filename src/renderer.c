# include "renderer.h"

uint32_t	ft_rgba(int red, int green, int blue, int alpha)
{
	uint32_t color = 0;
	color |= (alpha & 255) << 24;
	color |= (red & 255) << 16;
	color |= (green & 255) << 8;
	color |= (blue & 255);
	return (color);
}

uint32_t	ft_rgb(int red, int green, int blue)
{
	return (ft_rgba(red, green, blue, 0));
}

int		ft_is_rgb_mask(uint32_t color, u_int32_t mask)
{
	uint8_t r = (color >> 16) & 255;
	uint8_t g = (color >> 8) & 255;
	uint8_t b = color & 255;

	uint8_t rm = (mask >> 16) & 255;
	uint8_t gm = (mask >> 8) & 255;
	uint8_t bm = mask & 255;

	return (!(r != rm || g != gm || b != bm));
}

void	ft_glClear(void *instance, void *window)
{
	mlx_clear_window(instance, window);
}

void	ft_glBegin(void *instance, int width, int height, int mask)
{
	data.mask = mask;
	data.img = mlx_new_image(instance, width, height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
}

void	ft_glEnd(void *instance, void *window, int x, int y)
{
	if (data.img == NULL)
		return;

	mlx_put_image_to_window(instance, window, data.img, x, y);
	mlx_destroy_image(instance, data.img);
	data.img = NULL;
}

uint32_t	ft_glGetPixelColor(int x, int y, t_texture_data texture)
{
	char	*dst;

	dst = texture.address + (y * texture.line_length + x * (texture.bpp / 8));
	return (*(unsigned int*)dst);
}

void	ft_glPixel(t_vector point, unsigned int color)
{

	if (!ft_is_rgb_mask(color, data.mask))
	{
		char *dst;

		dst = data.addr + ((int) point.z * data.line_length + (int) point.x * (data.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	ft_glRectangle(t_vector origin, int width, int height, int color)
{
	int zo = (int)origin.z;
	int xo = (int)origin.x;
	while (origin.z < zo + height)
	{
		origin.x = xo;
		while (origin.x < xo + width)
		{
			ft_glPixel(origin, color);
			origin.x++;
		}
		origin.z++;
	}
}

void	ft_glRoundedRectangle(t_vector origin, int radius, int width, int height, int color)
{
	int x = origin.x;
	int z = origin.z;

	ft_glFilledCircle(new_vector(x + radius, z + radius), radius, color);
	ft_glFilledCircle(new_vector(x + radius + width - radius * 2, z + radius), radius, color);
	ft_glFilledCircle(new_vector(x + radius, z + radius + height - radius * 2), radius, color);
	ft_glFilledCircle(new_vector(x + radius + width - radius * 2, z + radius + height - radius * 2), radius, color);

	ft_glRectangle(new_vector(x + radius, z), width - radius * 2, radius, color);
	ft_glRectangle(new_vector(x + radius, z + height - radius), width - radius * 2, radius, color);
	ft_glRectangle(new_vector(x, z + radius), width, height - radius * 2, color);
}

void	ft_glRectangleTextured(t_vector origin, int width, int height, t_texture_data texture)
{
	int zo = (int)origin.z;
	int xo = (int)origin.x;

	double width_r = texture.texture_width / (double) width;
	double height_r = texture.texture_height / (double) height;

	while (origin.z < zo + height)
	{
		origin.x = xo;
		while (origin.x < xo + width)
		{
			ft_glPixel(origin, ft_glGetPixelColor((fabs(origin.x - xo) * width_r), fabs(origin.z - zo) * height_r, texture));
			origin.x++;
		}
		origin.z++;
	}
}

void	ft_glSkyBox(int offsetx, t_texture texture)
{
	int x;
	int y = 0;

	double width_r = data.textures[texture].texture_width / (double) RESOLUTION_WIDTH;
	double height_r = data.textures[texture].texture_height / (double) RESOLUTION_HEIGHT;

	while (y < RESOLUTION_HEIGHT / 2)
	{
		x = 0;
		while (x < RESOLUTION_WIDTH - offsetx)
		{
			ft_glPixel(new_vector(x, y), ft_glGetPixelColor((int)((x + offsetx) * width_r), (int)(y * height_r), texture));
			x++;
		}
		y++;
	}

	y = 0;
	while (y < RESOLUTION_HEIGHT / 2)
	{
		x = RESOLUTION_WIDTH - offsetx;
		while (x < RESOLUTION_WIDTH)
		{
			ft_glPixel(new_vector(x, y), ft_glGetPixelColor((int)((x - RESOLUTION_WIDTH + offsetx) * width_r), (int)(y * height_r), texture));
			x++;
		}
		y++;
	}
}

void	ft_glFilledCircle(t_vector origin, int radius, int color)
{
	for(int z = -radius; z <= radius; z++)
		for (int x = -radius; x <= radius; x++)
			if (x * x + z * z <= radius * radius)
				ft_glPixel(new_vector(origin.x + x, origin.z + z), color);
}

void	ft_glCircle(t_vector origin, int radius, int color)
{
	for (int i = 0; i <= 360; i++)
	{
		double x = sin(((i * M_PI) / 180)) * radius;
		double z = cos(((i * M_PI) / 180)) * radius;
		ft_glPixel(new_vector(origin.x + x, origin.z + z), color);
	}
}