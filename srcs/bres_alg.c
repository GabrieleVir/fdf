/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bres_alg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 06:18:16 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 05:52:39 by gvirga           ###   ########.fr       */
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

static void		trace_line(t_data **mai, t_bres *data)
{
	int			i;
	t_current	coords;
	intmax_t	pixel_pos;

	i = -1;
	coords.curr_x = (*data).x1;
	coords.curr_y = (*data).y1;
	while (++i <= (*data).long_dst)
	{
		pixel_pos = coords.curr_y * WIDTH + coords.curr_x;
		if ((pixel_pos >= 0 && pixel_pos < WIDTH * HEIGHT) &&
		coords.curr_x < WIDTH && coords.curr_x > 0 && coords.curr_y > 0 &&
		coords.curr_y < HEIGHT)
			((*mai)->mlx_data->img_add)[pixel_pos] = ((*mai)->force_color == 1)
				? 0x000001 : get_color(coords, data);
		(*data).numerator += (*data).shrt_dst;
		num_check(data, &(coords.curr_x), &(coords.curr_y));
	}
}

void			draw_line(t_data **mai, t_bres *data)
{
	if ((*mai)->force_color)
		change_img_add(mai);
	set_deltas(data);
	set_dst(data);
	trace_line(mai, data);
}
