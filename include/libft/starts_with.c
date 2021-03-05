#include "libft.h"

char	*ft_starts_with(char *string, char *charset)
{
	while (*charset)
	{
		if (*string != *charset)
			return (NULL);
		string++;
		charset++;
	}
	return (string);
}