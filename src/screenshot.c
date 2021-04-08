#include "cub3d.h"
#include "renderer.h"

static void		ft_file_screenshot(int fd, t_data *d, t_game *game)
{
	int i;
	int j;
	int color;
	
	i = game->res_height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < game->res_width)
		{
			color = *(int*)(d->address + (i * d->line_length
					+ j * (d->bpp / 8)));
			write(fd, &color, 4);
		}
	}
}

void		ft_screenshot2(t_data *d, int fd, t_game *game)
{
	int		size_screen;
	int		pos_pixel_data;
	int		zero;
	short	plane;

	plane = 1;
	zero = 0;
	pos_pixel_data = 54;
	size_screen = game->res_width
		* game->res_height * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pixel_data, 4);
	pos_pixel_data = 40;
	write(fd, &pos_pixel_data, 4);
	write(fd, &game->res_width, 4);
	write(fd, &game->res_height, 4);
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}
void		ft_screenshot(t_data *d, t_game *game)
{
	int fd;
	int size_screen;
	int zero;
	int size;
	fd = open("../screen.bmp", O_CREAT | O_RDWR, 0777);
	size_screen = game->res_width
		* game->res_height * 4 + 54;
	zero = 0;
	size = game->res_width
		* game->res_height;
	if (fd < 0)
		exit(1);
	ft_screenshot2(d, fd, game);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	size_screen = 1000;
	write(fd, &size_screen, 4);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	ft_file_screenshot(fd, d, game);
	close(fd);
}
