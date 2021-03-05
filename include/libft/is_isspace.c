#include "libft.h"

int		ft_is_isspace(int c)
{
	return (c == '\r' ||
			c == '\v' ||
			c == '\f' ||
			c == '\n' ||
			c == '\t' ||
			c == ' ');
}