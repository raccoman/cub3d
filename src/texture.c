# include "texture.h"

int	load_texture(void *mlx_instance, t_texture_data *save_to, char *resource)
{
	if (!(save_to->image = mlx_png_file_to_image(mlx_instance, resource, &save_to->width, &save_to->height)))
		return (FALSE);
	save_to->address = mlx_get_data_addr(save_to->image, &save_to->bpp, &save_to->line_length, &save_to->endian);
	return (save_to->address != NULL);
}