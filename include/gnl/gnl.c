/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raccoman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:38:45 by raccoman          #+#    #+#             */
/*   Updated: 2021/01/18 18:38:50 by raccoman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

void	ft_cache(char session[4096][BUFFER_SIZE],
				const int fd, const char *remaining)
{
	int	i;

	i = 0;
	while (remaining[i])
	{
		session[fd][i] = remaining[i];
		i++;
	}
	session[fd][i] = 0;
}

int		ft_decache(char session[4096][BUFFER_SIZE],
					const int fd, char **current)
{
	int i;
	int c;

	if (!(*current = ft_calloc(BUFFER_SIZE * 2, sizeof(char))))
		return (0);
	i = 0;
	c = 0;
	while (i < BUFFER_SIZE)
	{
		if (session[fd][i] != 0)
		{
			(*current)[c++] = session[fd][i];
			if (session[fd][i] == '\n')
			{
				session[fd][i] = 0;
				return (-1);
			}
			session[fd][i] = 0;
		}
		i++;
	}
	return (c);
}

int		ft_freemem(char **current, int toreturn)
{
	free(*current);
	*current = NULL;
	return (toreturn);
}

int		ft_compose(int result, char *current, char **line)
{
	int i;

	i = 0;
	while (current[i] && current[i] != '\n')
		i++;
	if (!(*line = ft_calloc(i + 1, sizeof(char))))
		return (ft_freemem(&current, -1));
	i = 0;
	while (current[i] && current[i] != '\n')
	{
		(*line)[i] = current[i];
		i++;
	}
	return (ft_freemem(&current, result == 0 ? 0 : 1));
}

int		gnl(int fd, char **line)
{
	static char	session[4096][BUFFER_SIZE];
	char		*current;
	char		*remaining;
	int			r;
	int			offset;

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || fd >= 4096)
		return (-1);
	offset = ft_decache(session, fd, &current);
	if (offset == -1)
		return (ft_compose(1, current, line));
	if (!current)
		return (-1);
	while ((r = read(fd, current + offset, BUFFER_SIZE)) > 0)
	{
		if ((remaining = ft_strchr(current, '\n')) != NULL)
		{
			ft_cache(session, fd, remaining);
			break ;
		}
		if (!(current = ft_strexpand(current, BUFFER_SIZE)))
			return (ft_freemem(&current, -1));
		offset += r;
	}
	return (r < 0 ? ft_freemem(&current, -1) : ft_compose(r, current, line));
}

int		ft_is_isspace(int c)
{
	return (c == '\r' ||
			c == '\v' ||
			c == '\f' ||
			c == '\n' ||
			c == '\t' ||
			c == ' ');
}

int		gnnel(int fd, char **line)
{
	char	*slider;
	int		res;

	while ((res = gnl(fd, line)) > 0)
	{
		slider = *line;
		while (is_isspace(*slider))
			slider++;
		if (*slider != 0)
			break;
		free(*line);
	}
	return (res);
}