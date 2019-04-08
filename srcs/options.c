/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:23:00 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/08 19:30:48 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_trans_map(t_data **map, int direction)
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

void	redraw_map(t_mlx **mlx, t_data **maps)
{
	mlx_destroy_image((*mlx)->mlx_ptr, (*mlx)->mlx_img);
	if (!(mlx_create_image(mlx)))
		exit(1);
	
}

int		deal_key(int key, t_data **mi)
{
	if (key == 53)
		exit(1);
	else if (key >= 123 && key <= 126)
	{
		move_trans_map(mi, key - 123);
		redraw_map(&((*mi)->mlx_data), mi);
	}
	return (0);
}

/*int		change_height(int key, int x, int y, t_data **mi)
  {
  return (0);
  }
  */
void		options_fdf(t_data **mi, t_mlx **mlx)
{
	mlx_key_hook((*mlx)->mlx_win, &deal_key, mi);
	//mlx_mouse_hook((*mlx)->mlx_win, &change_height, mi);
}
/*
   int		deal_key(int key, t_params *params)
   {
   t_map	*maps;
   t_mlx	*mlx_data;

   maps = params->maps;
   mlx_data = params->mlx_data;
   if (key == 53)
   exit(1);
   else if (key >= 123 && key <= 126)
   {
   move_trans_map(&maps, key - 123);
   redraw_map(&mlx_data, maps);
   }
   else if (key == 69 || key == 78)
   {
   if (zoom(&maps, key))
   redraw_map(&mlx_data, maps);
   }
   return (0);
   }
   */
/*
   int		change_height(int key, int x, int y, t_params *params)
   {
   t_map	*maps;
   t_mlx	*mlx_data;

   x = y;
   maps = params->maps;
   mlx_data		= params->mlx_data;
   if (key == 4 || key == 5)
   {
   move_z_value(&maps, key - 4);
   redraw_map(&mlx_data, maps);
   }
   return (0);
   }
   */

