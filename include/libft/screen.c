#include "libft.h"

unsigned int	ft_getscreen_width()
{
	long display;

	display = CGMainDisplayID();
	return (CGDisplayPixelsWide(display));
}

unsigned int	ft_getscreen_height()
{
	long display;

	display = CGMainDisplayID();
	return (CGDisplayPixelsHigh(display));
}
