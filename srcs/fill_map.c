/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:49:11 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 06:44:05 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void			trans_map(t_data **mai, int first_prog_launch, int projection)
{
	(*mai)->i = 0;
	if (first_prog_launch)
		set_dst_map(mai);
	while ((*mai)->i < (*mai)->nb_of_elems)
	{
		choosing_projection(mai, projection);
		((*mai)->i)++;
	}
}

/*
** coming from read_and_fill.c but, filling z_arr
*/

static void		set_z_values(t_data **m_i, int u)
{
	if (((*m_i)->trans_map)[u * 3 + 2] < 0)
	{
		if (labs(((*m_i)->trans_map)[u * 3 + 2]) > (*m_i)->biggest_z)
			(*m_i)->biggest_z = labs(((*m_i)->trans_map)[u * 3 + 2]);
	}
	else
	{
		if (((*m_i)->trans_map)[u * 3 + 2] > (*m_i)->biggest_z)
			(*m_i)->biggest_z = ((*m_i)->trans_map)[u * 3 + 2];
	}
	if ((*m_i)->trans_map[u * 3 + 2] > (*m_i)->highest_z)
		(*m_i)->highest_z = (*m_i)->trans_map[u * 3 + 2];
}

int				fill_z_arr(t_data **m_i, char *row, size_t i)
{
	size_t		u;

	u = 0 + (i * (*m_i)->nb_column);
	while (*row)
	{
		while (*row == ' ')
			row++;
		if (*row == '\0')
			break ;
		((*m_i)->trans_map)[u * 3 + 2] = ft_atoi(row);
		set_z_values(m_i, u);
		u++;
		while (*row && *row != ' ')
			row++;
	}
	return (1);
}
