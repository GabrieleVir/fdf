/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:49:11 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 05:49:31 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Perspective
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
	(*mai)->pad_x = 750;
	(*mai)->pad_y = 250;
}

void			trans_map(t_data **mai, int first_prog_launch)
{
	int		x;
	int		y;
	int		z;

	(*mai)->i = 0;
	if (first_prog_launch)
	{
		set_dst_map(mai);
		(*mai)->zoom = 1;
	}
	while ((*mai)->i < (*mai)->nb_of_elems)
	{
		x = (*mai)->i % (*mai)->nb_column * (*mai)->dst_x;
		y = ((*mai)->i / (*mai)->nb_column) * (*mai)->dst_y;
		z = (*mai)->trans_map[(*mai)->i * 3 + 2] * (*mai)->dst_z;
/*		(*mai)->trans_map[(*mai)->i * 3] = x * cos(0.523599) -
			y * cos(0.523599) + (*mai)->pad_x;
		(*mai)->trans_map[(*mai)->i * 3 + 1] = x * sin(0.523599) +
			y * sin(0.523599) - z + (*mai)->pad_y;*/
		(*mai)->trans_map[(*mai)->i * 3] = x + + (*mai)->pad_x;
		(*mai)->trans_map[(*mai)->i * 3 + 1] = y/2 - z + (*mai)->pad_y;
		((*mai)->i)++;
	}
}
