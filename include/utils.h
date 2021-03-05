#ifndef UTILS_H
#define UTILS_H

# include <math.h>

# define FALSE 0
# define TRUE 1

typedef struct	s_vector
{
	double	x;
	double	z;
}				t_vector;

t_vector		new_vector(double x, double z);

#endif
