/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:38:57 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/10 04:42:27 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move_z_value(t_data **mi, int direction)
{
	size_t		z0;
	size_t		z1;

	(*mi)->i = 0;
	while ((*mi)->i < (*mi)->nb_of_elems)
	{
		z0 = (*mi)->trans_map[(*mi)->i * 3 + 2] * (*mi)->dst_z;
		if (direction == 0)
			(*mi)->dst_z -= 1;
		else
			(*mi)->dst_z += 1;
		z1 = (*mi)->trans_map[(*mi)->i * 3 + 2] * (*mi)->dst_z;
		(*mi)->trans_map[(*mi)->i * 3 + 1] += (z0 - z1);
		((*mi)->i)++;
	}
}

int			change_height(int key, int x, int y, t_data **mi)
{
	x = y;
	if (key == 4 || key == 5)
	{
		move_z_value(mi, key - 4);
		mlx_destroy_image((*mi)->mlx_data->mlx_ptr, (*mi)->mlx_data->mlx_img);
		draw_map(mi, &((*mi)->mlx_data));
	}
	return (0);
}
