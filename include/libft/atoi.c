#include "libft.h"

int	ft_atoi(char **string)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	*string = skip_isspace(*string);
	while (**string == '+' || **string == '-')
	{
		sign = **string == '-' ? -1 : sign;
		(*string)++;
	}
	while (ft_isdigit(**string))
	{
		num *= 10;
		num += (**string) - 48;
		(*string)++;
	}
	return (num * sign);
}