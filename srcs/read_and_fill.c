/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:23:15 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/19 03:30:04 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		fill_z_arr(t_data **m_i, char *row, size_t i)
{
	size_t		u;

	u = 0 + (i * (*m_i)->nb_column);
	while (*row)
	{
		while (*row == ' ')
			row++;
		if (*row == '\0')
			break ;
		((*m_i)->z_arr)[u] = ft_atoi(row);
		u++;
		while (*row && *row != ' ')
			row++;
	}
	return (1);
}

static void		garbage_collector(char **data, char ***tmp_map, size_t nb_r)
{
	size_t		u;

	u = 0;
	while (u < nb_r)
	{
		free((*tmp_map)[u]);
		u++;
	}
	free(*tmp_map);
	free(*data);
	*data = NULL;
}

static int		fill_info(t_data **maps_info)
{
	size_t		i;
	char		**tmp_map;

	i = 0;
	(*maps_info)->nb_row = ft_wordcount((*maps_info)->data, '\n');
	if (!(tmp_map = ft_strsplit((*maps_info)->data, '\n')))
		return (error_file_msg(12, maps_info));
	(*maps_info)->nb_column = ft_wordcount(tmp_map[0], ' ');
	(*maps_info)->nb_of_elems = (*maps_info)->nb_row * (*maps_info)->nb_column;
	if (!((*maps_info)->z_arr = (intmax_t *)malloc(sizeof(intmax_t) *
			(*maps_info)->nb_of_elems)))
		return (error_file_msg(12, maps_info));
	while (i < (*maps_info)->nb_row)
	{
		if ((*maps_info)->nb_column != ft_wordcount(tmp_map[i], ' '))
			return (length_error_msg(&tmp_map, maps_info));
		fill_z_arr(maps_info, tmp_map[i], i);
		i++;
	}
	garbage_collector(&((*maps_info)->data), &tmp_map, (*maps_info)->nb_row);
	return (1);
}

int				read_file(t_data **maps_info, char *file_name)
{
	t_file		file;

	(*maps_info)->data = ft_strnew(0);
	if ((file.fd = open(file_name, O_RDONLY)) == -1)
		return (error_file_msg(2, maps_info));
	while ((file.ret = read(file.fd, file.buf, BUFF_SIZE)) > 0)
	{
		(file.buf)[file.ret] = '\0';
		if (!((*maps_info)->data = ft_strjoin_free((*maps_info)->data,
					file.buf, 1)))
			return (error_msg(12));
	}
	if (file.ret < 0)
		return (error_file_msg(9, maps_info));
	if ((*maps_info)->data[0] == '\0')
		return (error_empty_file(maps_info));
	close(file.fd);
	return (fill_info(maps_info));
}
