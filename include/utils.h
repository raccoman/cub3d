#ifndef UTILS_H
#define UTILS_H

# include <math.h>
# include "libft.h"

# define FALSE 0
# define TRUE 1
# define MAX(a, b) a > b ? a : b
# define MIN(a, b) a < b ? a : b

typedef struct	s_vector
{
	double	x;
	double	z;
}				t_vector;

t_vector		new_vector(double x, double z);

#endif
