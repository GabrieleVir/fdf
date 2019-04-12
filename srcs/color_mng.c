/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:18:18 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 05:44:50 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

static double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int				get_color(t_current current, t_bres *data)
{
	int		green;
	int		red;
	int		blue;
	double	percentage;

	if ((*data).start_color == (*data).end_color)
		return ((*data).end_color);
	if ((*data).width > (*data).height)
		percentage = percent((*data).x1, (*data).x2, current.curr_x);
	else
		percentage = percent((*data).y1, (*data).y2, current.curr_y);
   red = get_light(((*data).start_color >> 16) & 0xFF,
		   ((*data).end_color >> 16) & 0xFF, percentage);
   green = get_light(((*data).start_color >> 8) & 0xFF,
		   ((*data).end_color >> 8) & 0xFF, percentage);
   blue = get_light((*data).start_color & 0xFF,
		   (*data).end_color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
