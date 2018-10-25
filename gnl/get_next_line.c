/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 22:33:32 by gvirga            #+#    #+#             */
/*   Updated: 2018/10/15 16:51:18 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		negative_return_managment(char rest[BUFF_SIZE])
{
	ft_bzero(rest, BUFF_SIZE + 1);
	return (-1);
}

static int		line_in_buffer(int i, char **line, char rest[BUFF_SIZE])
{
	char	*tmp;
	int		u;

	if ((i = (int)ft_strchri(rest, '\n') - 1) != -1)
	{
		u = -1;
		if ((tmp = ft_strnjoin(*line, rest, i)) == NULL)
			return (negative_return_managment(rest));
		while (rest[i])
			rest[++u] = rest[++i];
		free(*line);
		*line = tmp;
		return (1);
	}
	else
	{
		if ((tmp = ft_strjoin(*line, rest)) == NULL)
			return (negative_return_managment(rest));
		free(*line);
		ft_bzero(rest, BUFF_SIZE + 1);
		*line = tmp;
		return (0);
	}
}

static int		reading_next_line(int fd, char **line, char rest[BUFF_SIZE])
{
	int		ret;
	int		i;

	if ((*line = ft_strnew(ft_strlen(rest))) == NULL)
		return (negative_return_managment(rest));
	ft_strcpy(*line, rest);
	ft_bzero(rest, BUFF_SIZE + 1);
	while ((ret = read(fd, rest, BUFF_SIZE)) > 0)
	{
		rest[ret] = '\0';
		if ((i = line_in_buffer(0, line, rest)) != 0)
			return (i);
	}
	if (**line)
		return (1);
	if (ret == -1)
		return (negative_return_managment(rest));
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static char		rest_arr[OPEN_MAX][BUFF_SIZE + 1];
	size_t			i;
	int				u;

	if ((fd < 0 || fd >= OPEN_MAX) || line == NULL)
		return (-1);
	i = 0;
	while (rest_arr[fd][i])
	{
		if (rest_arr[fd][i] == '\n')
		{
			u = -1;
			if ((*line = ft_strsub(rest_arr[fd], 0, i)) == NULL)
				return (negative_return_managment(rest_arr[fd]));
			if (rest_arr[fd][i + 1] == '\0')
				ft_bzero(rest_arr[fd], BUFF_SIZE);
			else
				while (rest_arr[fd][i])
					rest_arr[fd][++u] = rest_arr[fd][++i];
			return (1);
		}
		i++;
	}
	return (reading_next_line(fd, line, rest_arr[fd]));
}
