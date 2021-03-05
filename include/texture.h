#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct	s_texture_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		texture_width;
	int		texture_height;
}				t_texture_data;

#endif
