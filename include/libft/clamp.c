#include "libft.h"

int	ft_max(int v, int max)
{
	return (v > max ? v : max);
}

int	ft_min(int v, int min)
{
	return (v > min ? min : v);
}

int	ft_clamp(int v, int max, int min)
{
	return (ft_max(min, ft_min(v, max)));
}