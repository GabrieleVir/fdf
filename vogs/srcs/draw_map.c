/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 06:14:17 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 02:40:33 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** 1 for the next point in x and 2 for next point in y
*/

static int		check_part(intmax_t highest_z, intmax_t z)
{
	int		i;

	i = -1;
	while (++i < 8)
	{
		if (labs(z) >= (((8 - i) * highest_z) / 8))
			return (i + 1);
	}
	return (9);
}

static void		set_colors(t_bres *data, t_data **mai)
{
	(*data).start_color = (*mai)->highest_color /
		check_part((*mai)->highest_z, (*data).z1);
	(*data).end_color = (*mai)->highest_color /
		check_part((*mai)->highest_z, (*data).z2);
}

static void		prepare_data_bres(t_bres *data, int x_or_y, t_data **mai)
{
	if (x_or_y == 1)
	{
		(*data).x1 = (*mai)->trans_map[(*mai)->i * 3];
		(*data).x2 = (*mai)->trans_map[((*mai)->i + 1) * 3];
		(*data).y1 = (*mai)->trans_map[(*mai)->i * 3 + 1];
		(*data).y2 = (*mai)->trans_map[((*mai)->i + 1) * 3 + 1];
		(*data).z1 = (*mai)->trans_map[(*mai)->i * 3 + 2];
		(*data).z2 = (*mai)->trans_map[((*mai)->i + 1) * 3 + 2];
		set_colors(data, mai);
	}
	else
	{
		(*data).x1 = (*mai)->trans_map[(*mai)->i * 3];
		(*data).x2 = (*mai)->trans_map[((*mai)->i + (*mai)->nb_column) * 3];
		(*data).y1 = (*mai)->trans_map[(*mai)->i * 3 + 1];
		(*data).y2 = (*mai)->trans_map[
			((*mai)->i + (*mai)->nb_column) * 3 + 1];
		(*data).z1 = (*mai)->trans_map[(*mai)->i * 3 + 2];
		(*data).z2 = (*mai)->trans_map[((*mai)->i + (*mai)->nb_column) * 3 + 2];
		set_colors(data, mai);
	}
}

int				draw_map(t_data **mai, t_mlx **m_i)
{
	t_bres		data;

	(*mai)->i = 0;
	mlx_create_image(m_i);
	while ((*mai)->i < (*mai)->nb_of_elems)
	{
		if (((*mai)->i + 1) % (*mai)->nb_column != 0)
		{
			prepare_data_bres(&data, 1, mai);
			draw_line(mai, &data);
		}
		if (((*mai)->i + (*mai)->nb_column) < (*mai)->nb_of_elems)
		{
			prepare_data_bres(&data, 2, mai);
			draw_line(mai, &data);
		}
		((*mai)->i)++;
	}
	mlx_put_image_to_window((*m_i)->mlx_ptr, (*m_i)->mlx_win, (*m_i)->mlx_img,
			0, 0);
	return (1);
}
