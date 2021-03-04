#ifndef LIBFT_H
#define LIBFT_H

# include <CoreGraphics/CGDisplayConfiguration.h>

int		is_isspace(int c);

char	*skip_isspace(char *string);

int		ft_atoi(char **string);

int		ft_isdigit(int c);

unsigned int	ft_getscreen_width();

unsigned int	ft_getscreen_height();

int	ft_max(int v, int max);

int	ft_min(int v, int min);

int	ft_clamp(int v, int max, int min);

#endif
