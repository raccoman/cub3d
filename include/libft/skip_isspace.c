#include "libft.h"

char	*skip_isspace(char *string)
{
	while (*string && is_isspace(*string))
		string++;
	return (string);
}