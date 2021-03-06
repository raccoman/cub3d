#include "libft.h"

int	ft_find(char *string, char *charset)
{
	int i;

	i = 0;
	while (string[i])
	{
		if (ft_contains(charset, string[i]))
			return (i);
		i++;
	}
	return (-1);
}