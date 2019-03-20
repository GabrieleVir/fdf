/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bres_alg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 06:18:16 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/20 06:58:42 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_dst(t_bres *data)
{
	if ((*data).width > (*data).height)
	{
		(*data).long_dst = labs((*data).width);
		(*data).shrt_dst = labs((*data).height);
	}
	else
	{
		(*data).long_dst = labs((*data).height);
		(*data).shrt_dst = labs((*data).width);
		if ((*data).height < 0)
			(*data).dy2 = -1;
		else
			(*data).dy2 = 1;
		(*data).dx2 = 0;
	}
	(*data).numerator = (*data).long_dst / 2;
}

static void		set_deltas(t_bres *data)
{
	(*data).width = (*data).x2 - (*data).x1;
	(*data).height = (*data).y2 - (*data).y1;
	(*data).dx1 = 0;
	(*data).dx2 = 0;
	(*data).dy1 = 0;
	(*data).dy2 = 0;
	if ((*data).width < 0)
	{
		(*data).dx1 = -1;
		(*data).dx2 = -1;
	}
	else
	{
		(*data).dx1 = -1;
		(*data).dx2 = -1;
	}
	if ((*data).height < 0)
		(*data).dy1 = -1;
	else
		(*data).dy1 = 1;
}

static void		trace_line(t_data **mai, t_bres *data)
{
	int			i;

	i = -1;
	while (++i <= (*data).long_dst)
	{
		((*mai)->mlx_data->img_add)
			[(*data).x1 + (*data).y1 * WIDTH] = 0x0000FF;
		(*data).numerator += (*data).shrt_dst;
		if ((*data).numerator > (*data).long_dst)
		{
			(*data).numerator -= (*data).long_dst;
			(*data).x1 += (*data).dx1;
			(*data).y1 += (*data).dy1;
		}
		else
		{
			(*data).x1 += (*data).dx2;
			(*data).y1 += (*data).dy2;
		}
	}
}

void			draw_line(t_data **mai, t_bres *data)
{
	set_deltas(data);
	set_dst(data);
	trace_line(mai, data);
}
