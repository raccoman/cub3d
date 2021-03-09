#include "libft.h"

int	ft_irandom(int min, int max)
{
	return (rand() % (max - min)) + min;
}