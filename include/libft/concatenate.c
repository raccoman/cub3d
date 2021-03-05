#include "libft.h"

char	*ft_concatenate(char *s1, char *s2)
{
	int		i;
	int		k;
	char	*string;

	k = 0;
	if (!(string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[k] = s1[i];
		i++;
		k++;
	}
	i = 0;
	while (s2[i])
	{
		string[k] = s2[i];
		i++;
		k++;
	}
	string[k] = 0;
	return (string);
}