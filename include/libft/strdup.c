#include "libft.h"

char *ft_strdup(char *string)
{
	int i;
	char *new_string;

	if (!(new_string = malloc(sizeof(char) * (ft_strlen(string) + 1))))
		return (NULL);
	i = 0;
	while (string[i])
	{
		new_string[i] = string[i];
		i++;
	}
	new_string[i] = 0;
	return (new_string);
}