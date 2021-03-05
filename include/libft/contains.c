#include "libft.h"

int		ft_contains(char *string, int c)
{
	while (*string)
	{
		if (*string == c)
			return (1);
		string++;
	}
	return (0);
}