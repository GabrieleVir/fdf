/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   black_and_white.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 03:36:35 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 03:58:24 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	black_and_white(t_data **mi)
{
	static int		active = 1;

	mlx_destroy_image((*mi)->mlx_data->mlx_ptr, (*mi)->mlx_data->mlx_img);
	if (active)
	{
		(*mi)->force_color = 1;
		active = 0;
	}
	else
	{
		(*mi)->force_color = 0;
		active = 1;
	}
	draw_map(mi, &((*mi)->mlx_data));
}

void	change_img_add(t_data **mai)
{
	size_t		i;

	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		if (((*mai)->mlx_data->img_add)[i] == 0xFFFFFF)
			break ;
		if (((*mai)->mlx_data->img_add)[i] == 0)
			((*mai)->mlx_data->img_add)[i] = 0xFFFFFF;
		i++;
	}
}
