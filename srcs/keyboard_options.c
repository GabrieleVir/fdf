/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:39:56 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 06:02:56 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move_trans_map(t_data **map, int direction)
{
	size_t		i;
	int			padding_value;

	i = -1;
	if (direction == 0 || direction == 1)
	{
		padding_value = (direction == 0) ? -100 : 100;
		(*map)->pad_x += padding_value;
		while (++i < (*map)->nb_of_elems)
			(*map)->trans_map[i * 3] += padding_value;
	}
	else if (direction == 2 || direction == 3)
	{
		padding_value = (direction == 2) ? 100 : -100;
		(*map)->pad_y += padding_value;
		while (++i < (*map)->nb_of_elems)
			(*map)->trans_map[i * 3 + 1] += padding_value;
	}
}

static void	zoom_up(t_data **map)
{
	if ((*map)->dst_x > 25 && (*map)->dst_y > 25)
	{
		(*map)->dst_x += 5;
		(*map)->dst_y += 5;
		trans_map(map, 0);
	}
	else
	{
		(*map)->dst_x += 1;
		(*map)->dst_y += 1;
		trans_map(map, 0);
	}
}

static int	zoom(t_data **map, int zoom)
{
	(*map)->i = -1;
	if (zoom == 69)
		zoom_up(map);
	else
	{
		if ((*map)->dst_x > 25 && (*map)->dst_y > 25)
		{
			(*map)->dst_x -= 5;
			(*map)->dst_y -= 5;
			trans_map(map, 0);
		}
		else if ((*map)->dst_x > 1 && (*map)->dst_y > 1)
		{
			(*map)->dst_x -= 1;
			(*map)->dst_y -= 1;
			trans_map(map, 0);
		}
		else
			return (-1);
	}
	return (1);
}

int			deal_key(int key, t_data **mi)
{
	if (key == 53)
		exit(1);
	else if (key >= 123 && key <= 126)
	{
		move_trans_map(mi, key - 123);
		mlx_destroy_image((*mi)->mlx_data->mlx_ptr, (*mi)->mlx_data->mlx_img);
		draw_map(mi, &((*mi)->mlx_data));
	}
	else if (key == 69 || key == 78)
	{
		if (zoom(mi, key))
		{
			mlx_destroy_image((*mi)->mlx_data->mlx_ptr,
				(*mi)->mlx_data->mlx_img);
			draw_map(mi, &((*mi)->mlx_data));
		}
	}
	if (key == 45)
		black_and_white(mi);
	return (0);
}
