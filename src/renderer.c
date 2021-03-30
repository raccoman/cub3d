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
	data.image = mlx_new_image(instance, width, height);
	data.address = mlx_get_data_addr(data.image, &data.bpp, &data.line_length, &data.endian);
}

void	ft_glEnd(void *instance, void *window, int x, int y)
{
	if (data.image == NULL)
		return;

	mlx_put_image_to_window(instance, window, data.image, x, y);
	mlx_destroy_image(instance, data.image);
	data.image = NULL;
}

uint32_t	ft_glGetPixelColor(int x, int y, t_texture_data texture)
{
	char	*dst;

	dst = texture.address + (y * texture.line_length + x * (texture.bpp / 8));
	return (*(unsigned int*)dst);
}

void ft_glPixel(int x, int y, uint32_t color)
{

	if (!ft_is_rgb_mask(color, data.mask))
	{
		char *dst;

		dst = data.address + ((int) y * data.line_length + (int) x * (data.bpp / 8));
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
			ft_glPixel((int)origin.x, (int)origin.z, color);
			origin.x++;
		}
		origin.z++;
	}
}

void	ft_glRoundedRectangle(t_vector origin, int radius, int width, int height, int color)
{
	int x = (int)origin.x;
	int z = (int)origin.z;

	ft_glFilledCircle(vector(x + radius, z + radius), radius, color);
	ft_glFilledCircle(vector(x + radius + width - radius * 2, z + radius), radius, color);
	ft_glFilledCircle(vector(x + radius, z + radius + height - radius * 2), radius, color);
	ft_glFilledCircle(vector(x + radius + width - radius * 2, z + radius + height - radius * 2), radius, color);

	ft_glRectangle(vector(x + radius, z), width - radius * 2, radius, color);
	ft_glRectangle(vector(x + radius, z + height - radius), width - radius * 2, radius, color);
	ft_glRectangle(vector(x, z + radius), width, height - radius * 2, color);
}

void	ft_glRecText(t_vector origin, int width, int height, t_texture_data texture)
{
	int zo = (int)origin.z;
	int xo = (int)origin.x;

	double width_r = texture.width / (double) width;
	double height_r = texture.height / (double) height;

	while (origin.z < zo + height)
	{
		origin.x = xo;
		while (origin.x < xo + width)
		{
			ft_glPixel((int)origin.x, (int)origin.z, ft_glGetPixelColor((int)(fabs(origin.x - xo) * width_r), (int)(fabs(origin.z - zo) * height_r), texture));
			origin.x++;
		}
		origin.z++;
	}
}

void	ft_glSkyBox(int offsetx, int offsety, int res_width, int res_height, t_texture_data texture)
{
	int	x;
	int	z;
	int	horizon;

	double width_r = texture.width / (double) res_width;
	double height_r = texture.height / (double) res_height;

	z = 0;
	while (z < res_height)
	{
		horizon = z + 160 - res_height / 2 + offsety;
		x = 0;
		while (x < res_width - offsetx)
		{
			ft_glPixel(x, z + horizon - z, ft_glGetPixelColor((int)((x + offsetx) * width_r), (int)(z * height_r), texture));
			x++;
		}

		x = res_width - offsetx;
		while (x < res_width)
		{
			ft_glPixel(x, z + horizon - z, ft_glGetPixelColor((int)((x - res_width + offsetx) * width_r), (int)(z * height_r), texture));
			x++;
		}

		z++;
	}
}

void	ft_glFilledCircle(t_vector origin, int radius, int color)
{
	for(int z = -radius; z <= radius; z++)
		for (int x = -radius; x <= radius; x++)
			if (x * x + z * z <= radius * radius)
				ft_glPixel((int)(origin.x + x), (int)(origin.z + z), color);
}

void	ft_glCircle(t_vector origin, int radius, int color)
{
	for (int i = 0; i <= 360; i++)
	{
		double x = sin(((i * M_PI) / 180)) * radius;
		double z = cos(((i * M_PI) / 180)) * radius;
		ft_glPixel((int)(origin.x + x), (int)(origin.z + z), color);
	}
}

double	scale_w(double v, int width)
{
	return (v * width / 1280.0);
}

double	scale_h(double v, int height)
{
	return (v * height / 720.0);
}