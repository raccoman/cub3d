#include "libft.h"

char	*ft_terminate_at(char *string, char *charset)
{
	int i;

	i = 0;
	while (string[i])
	{
		if (ft_contains(charset, string[i]))
		{
			string[i] = 0;
			break;
		}
		i++;
	}
	return (string);
}