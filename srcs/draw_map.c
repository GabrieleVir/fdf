/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 06:14:17 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/08 19:27:33 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** 1 for the next point in x and 2 for next point in y
*/

static void		prepare_data_bres(t_bres *data, int x_or_y, t_data **mai)
{
	if (x_or_y == 1)
	{
		(*data).x1 = (*mai)->trans_map[(*mai)->i * 3];
		(*data).x2 = (*mai)->trans_map[((*mai)->i + 1) * 3];
		(*data).y1 = (*mai)->trans_map[(*mai)->i * 3 + 1];
		(*data).y2 = (*mai)->trans_map[((*mai)->i + 1) * 3 + 1];
	}
	else
	{
		(*data).x1 = (*mai)->trans_map[(*mai)->i * 3];
		(*data).x2 = (*mai)->trans_map[((*mai)->i + (*mai)->nb_column) * 3];
		(*data).y1 = (*mai)->trans_map[(*mai)->i * 3 + 1];
		(*data).y2 = (*mai)->trans_map[
			((*mai)->i + (*mai)->nb_column) * 3 + 1];
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