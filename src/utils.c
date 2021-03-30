# include "utils.h"

t_vector	vector(double x, double z)
{
	t_vector vector;

	vector.x = x;
	vector.z = z;
	return (vector);
}

int64_t	hp_to_color(int hp)
{
	if (hp >= 50)
		return (0x2CC91E);
	else if (hp >= 20)
		return (0xF2BA35);
	else
		return (0xAD271D);
}