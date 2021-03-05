#include "libft.h"

int	ft_contains_only(char *string, char *charset)
{
	while (*string)
	{
		if (!ft_contains(charset, *string))
			return (0);
		string++;
	}
	return (1);
}