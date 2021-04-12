#include "../headers/renderer.h"

/*
**	Norminette V3 Status: OK!
*/

typedef struct s_font
{
	int			dx;
	int			dy;
	int			fx;
	int			fy;
	int			width;
	int			height;
	int			c;
	int			max;
	uint32_t	color;
}		t_font;

void	ft_printChar(t_font *font, t_texture_data texture, int y)
{
	while (font->fx < (font->c % 8) * font->width + font->width)
	{
		font->dy = y;
		font->fy = font->c / 8 * font->height;
		while (font->fy < font->c / 8 * font->height + font->height)
		{
			font->color = ft_glGetPixelColor(font->fx, font->fy, texture);
			ft_glPixel(font->dx, font->dy, font->color);
			if (font->color != 0x00FF00 && font->max < font->dx)
				font->max = font->dx;
			font->dy++;
			font->fy++;
		}
		font->dx++;
		font->fx++;
	}
}

void	ft_glString(int x, int y, const char *string, t_texture_data texture)
{
	t_font	font;
	int		i;

	font.width = texture.width / 8;
	font.height = texture.height / 12;
	i = 0;
	font.dx = x;
	font.max = 0;
	while (string[i])
	{
		font.c = (string[i] - '!');
		font.fx = (font.c % 8) * font.width;
		ft_printChar(&font, texture, y);
		font.dx -= font.dx - font.max;
		i++;
	}
}
