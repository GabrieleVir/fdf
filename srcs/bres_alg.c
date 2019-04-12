/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bres_alg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 06:18:16 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 02:32:47 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_dst(t_bres *data)
{
	(*data).long_dst = labs((*data).width);
	(*data).shrt_dst = labs((*data).height);
	if ((*data).long_dst < (*data).shrt_dst)
	{
		(*data).long_dst = labs((*data).height);
		(*data).shrt_dst = labs((*data).width);
		if ((*data).height < 0)
			(*data).dy2 = -1;
		else
			(*data).dy2 = 1;
		(*data).dx2 = 0;
	}
	(*data).numerator = (*data).long_dst >> 1;
}

static void		set_deltas(t_bres *data)
{
	(*data).width = (*data).x2 - (*data).x1;
	(*data).height = (*data).y2 - (*data).y1;
	(*data).dy2 = 0;
	if ((*data).width < 0)
	{
		(*data).dx1 = -1;
		(*data).dx2 = -1;
	}
	else
	{
		(*data).dx1 = 1;
		(*data).dx2 = 1;
	}
	if ((*data).height < 0)
		(*data).dy1 = -1;
	else
		(*data).dy1 = 1;
}

static void		num_check(t_bres *data, int *curr_x, int *curr_y)
{
	if ((*data).numerator >= (*data).long_dst)
	{
		(*data).numerator -= (*data).long_dst;
		(*curr_x) += (*data).dx1;
		(*curr_y) += (*data).dy1;
	}
	else
	{
		(*curr_x) += (*data).dx2;
		(*curr_y) += (*data).dy2;
	}
}
/*
		get_percentage();
		get_light();
		get_color();
*/
static void		trace_line(t_data **mai, t_bres *data)
{
	int			i;
	int			curr_x;
	int			curr_y;
	intmax_t	pixel_pos;

	i = -1;
	curr_x = (*data).x1;
	curr_y = (*data).y1;
	while (++i <= (*data).long_dst)
	{
		pixel_pos = curr_y * WIDTH + curr_x;
		if ((pixel_pos >= 0 && pixel_pos < WIDTH * HEIGHT) && curr_x <
		WIDTH && curr_x > 0 && curr_y > 0 && curr_y < HEIGHT)
			((*mai)->mlx_data->img_add)[pixel_pos] = (*data).start_color;
		(*data).numerator += (*data).shrt_dst;
		num_check(data, &curr_x, &curr_y);
	}
}

void			draw_line(t_data **mai, t_bres *data)
{
	set_deltas(data);
	set_dst(data);
	trace_line(mai, data);
}
