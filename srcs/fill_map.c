/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:49:11 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/10 04:51:37 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Perspective
** (*mai)->trans_map[i * 3] = x + 750;
** (*mai)->trans_map[i * 3 + 1] = y/2 - z + 250;
*/

static void		set_dst_map(t_data **mai)
{
	(*mai)->dst_x = (WIDTH / 2) / (*mai)->nb_column;
	if ((*mai)->dst_x < 10)
		(*mai)->dst_x = 10;
	(*mai)->dst_y = (HEIGHT / 2) / (*mai)->nb_row;
	if ((*mai)->dst_y < 10)
		(*mai)->dst_y = 10;
	(*mai)->dst_z = (HEIGHT / 200 / (*mai)->biggest_z);
	if ((*mai)->dst_z == 0)
		(*mai)->dst_z = 1;
}

void			trans_map(t_data **mai)
{
	size_t	i;
	int		x;
	int		y;
	int		z;

	i = 0;
	set_dst_map(mai);
	while (i < (*mai)->nb_row * (*mai)->nb_column)
	{
		x = i % (*mai)->nb_column * (*mai)->dst_x;
		y = (i / (*mai)->nb_column) * (*mai)->dst_y;
		z = (*mai)->trans_map[i * 3 + 2] * (*mai)->dst_z;
		(*mai)->trans_map[i * 3] = x * cos(0.523599) - y * cos(0.523599) +
			750;
		(*mai)->trans_map[i * 3 + 1] = x * sin(0.523599) + y * sin(0.523599)
			- z + 250;
		i++;
	}
}
