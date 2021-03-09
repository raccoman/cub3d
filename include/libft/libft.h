#ifndef LIBFT_H
#define LIBFT_H

# include <stdlib.h>
# include <CoreGraphics/CGDisplayConfiguration.h>

int		ft_is_isspace(int c);

int		ft_contains(char *string, int c);

char	*ft_skip_charset(char *string, char *charset);

int		ft_atoi(char **string);

int		ft_isdigit(int c);

unsigned int	ft_getscreen_width();

unsigned int	ft_getscreen_height();

int		ft_max(int v, int max);

int		ft_min(int v, int min);

int		ft_clamp(int v, int max, int min);

char	*ft_starts_with(char *string, char *charset);

int		ft_contains_only(char *string, char *charset);

char	*ft_strdup(char *string);

size_t	ft_strlen(char *string);

char	*ft_terminate_at(char *string, char *charset);

char	*ft_concatenate(char *s1, char *s2);

int		ft_find(char *string, char *charset);

int		ft_irandom(int min, int max);

#endif
