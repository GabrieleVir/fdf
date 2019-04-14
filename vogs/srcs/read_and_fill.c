/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:23:15 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 06:33:36 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static void		set_z_for_color(t_data **maps_info)
{
	(*maps_info)->highest_z = 0;
	(*maps_info)->highest_color = 0xFF0000;
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
	if (!((*maps_info)->trans_map = (intmax_t *)malloc(sizeof(intmax_t) *
			(*maps_info)->nb_of_elems * 3)))
		return (error_file_msg(12, maps_info));
	set_z_for_color(maps_info);
	while (i < (*maps_info)->nb_row)
	{
		if ((*maps_info)->nb_column != ft_wordcount(tmp_map[i], ' '))
			return (length_error_msg(&tmp_map, maps_info));
		(*maps_info)->biggest_z = 1;
		fill_z_arr(maps_info, tmp_map[i], i);
		i++;
	}
	(*maps_info)->projection = 0;
	trans_map(maps_info, 1, (*maps_info)->projection);
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
