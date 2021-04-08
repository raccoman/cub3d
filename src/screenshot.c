// static void		ft_file_screenshot(int fd, t_data *d) //t_data > ~t_image
// {
// 	int i;
// 	int j;
// 	int color;
// ​
// 	i = d->height;
// 	while (--i >= 0)
// 	{
// 		j = -1;
// 		while (++j < d->width)
// 		{
// 			color = *(int*)(d->addr + (i * d->line_len
// 					+ j * (d->bpp / 8)));
// 			write(fd, &color, 4);
// 		}
// 	}
// }
// ​
// void		ft_screenshot2(t_data *d, int fd)
// {
// 	int		size_screen;
// 	int		pos_pixel_data;
// 	int		zero;
// 	short	plane;
// ​
// 	plane = 1;
// 	zero = 0;
// 	pos_pixel_data = 54;
// 	size_screen = d->width
// 		* d->height * 4 + 54;
// 	write(fd, "BM", 2);
// 	write(fd, &size_screen, 4);
// 	write(fd, &zero, 4);
// 	write(fd, &pos_pixel_data, 4);
// 	pos_pixel_data = 40;
// 	write(fd, &pos_pixel_data, 4);
// 	write(fd, &d->width, 4);
// 	write(fd, &d->height, 4);
// 	write(fd, &plane, 2);
// 	plane = 32;
// 	write(fd, &plane, 2);
// }
// ​
// void		screenshot(t_data *d)
// {
// 	int fd;
// 	int size_screen;
// 	int zero;
// 	int size;
// ​
// 	fd = open("screen.bmp", O_CREAT | O_RDWR, 0777);
// 	size_screen = d->width
// 		* d->height * 4 + 54;
// 	zero = 0;
// 	size = d->width
// 		* d->height;
// 	if (fd < 0)
// 		ft_putendl_fd("Error", 2);
// 	ft_screenshot2(d, fd);
// 	write(fd, &zero, 4);
// 	write(fd, &size, 4);
// 	size_screen = 1000;
// 	write(fd, &size_screen, 4);
// 	write(fd, &size_screen, 4);
// 	write(fd, &zero, 4);
// 	write(fd, &zero, 4);
// 	ft_file_screenshot(fd, d);
// 	close(fd);
// 	my_exit(d);
// }
