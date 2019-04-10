/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:39:56 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/10 04:50:51 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move_trans_map(t_data **map, int direction)
{
	size_t		i;

	i = -1;
	if (direction == 0)
		while (++i < (*map)->nb_column * (*map)->nb_row)
			(*map)->trans_map[i * 3] -= 100;
	else if (direction == 2)
		while (++i < (*map)->nb_column * (*map)->nb_row)
			(*map)->trans_map[i * 3 + 1] += 100;
	else if (direction == 1)
		while (++i < (*map)->nb_column * (*map)->nb_row)
			(*map)->trans_map[i * 3] += 100;
	else
	{
		while (++i < (*map)->nb_column * (*map)->nb_row)
			(*map)->trans_map[i * 3 + 1] -= 100;
	}
}

static void	zoom_up(int *max_zoom, t_data **map, int *min_zoom)
{
	if (*max_zoom < 3)
	{
		(*max_zoom)++;
		(*min_zoom)--;
		while (++(*map)->i < (*map)->nb_of_elems)
		{
			(*map)->trans_map[(*map)->i * 3] *= 2;
			(*map)->trans_map[(*map)->i * 3 + 1] *= 2;
		}
	}
	else
		return ;
}

static int	zoom(t_data **map, int zoom)
{
	static int	max_zoom = 0;
	static int	min_zoom = 0;

	(*map)->i = -1;
	if (zoom == 69)
		zoom_up(&max_zoom, map, &min_zoom);
	else
	{
		if (min_zoom < 0)
		{
			min_zoom++;
			max_zoom--;
			while (++(*map)->i < (*map)->nb_of_elems)
			{
				if ((*map)->trans_map[(*map)->i * 3] != 1)
					(*map)->trans_map[(*map)->i * 3] /= 2;
				if ((*map)->trans_map[(*map)->i * 3 + 1] != 1)
					(*map)->trans_map[(*map)->i * 3 + 1] /= 2;
			}
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
	return (0);
}
