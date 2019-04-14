/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:11:21 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/14 23:59:53 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	isometric_projection(t_data **mai)
{
	int		x;
	int		y;
	int		z;

	x = (*mai)->i % (*mai)->nb_column * (*mai)->dst_x;
	y = ((*mai)->i / (*mai)->nb_column) * (*mai)->dst_y;
	z = (*mai)->trans_map[(*mai)->i * 3 + 2] * (*mai)->dst_z;
	(*mai)->trans_map[(*mai)->i * 3] = x * cos(0.523599) -
		y * cos(0.523599) + (*mai)->pad_x;
	(*mai)->trans_map[(*mai)->i * 3 + 1] = x * sin(0.523599) +
		y * sin(0.523599) - z + (*mai)->pad_y;
}

static void	perspective_projection(t_data **mai)
{
	int		x;
	int		y;
	int		z;

	x = (*mai)->i % (*mai)->nb_column * (*mai)->dst_x;
	y = ((*mai)->i / (*mai)->nb_column) * (*mai)->dst_y;
	z = (*mai)->trans_map[(*mai)->i * 3 + 2] * (*mai)->dst_z;
	(*mai)->trans_map[(*mai)->i * 3] = x + (*mai)->pad_x;
	(*mai)->trans_map[(*mai)->i * 3 + 1] = y / 2 - z + (*mai)->pad_y;
}

void		choosing_projection(t_data **mai, int projection)
{
	if (projection == 0)
		isometric_projection(mai);
	else if (projection == 1)
		perspective_projection(mai);
	else
		exit(1);
}

void		change_perspective(t_data **mi)
{
	static int		projection = 0;

	if (!projection)
	{
		(*mi)->projection = 1;
		projection = 1;
	}
	else
	{
		(*mi)->projection = 0;
		projection = 0;
	}
	trans_map(mi, 0, (*mi)->projection);
	mlx_destroy_image((*mi)->mlx_data->mlx_ptr, (*mi)->mlx_data->mlx_img);
	draw_map(mi, &((*mi)->mlx_data));
}
