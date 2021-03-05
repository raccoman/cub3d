#include "libft.h"

char	*ft_skip_charset(char *string, char *charset)
{
	while (*string && ft_contains(charset, *string))
		string++;
	return (string);
}