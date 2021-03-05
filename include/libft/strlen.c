#include "libft.h"

size_t	ft_strlen(char *string)
{
	size_t i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}