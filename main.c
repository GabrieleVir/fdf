/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 23:24:51 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/19 05:25:41 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 */

int		mlx_starting(t_mlx **m_i)
{

	if (!((*m_i)->mlx_ptr = mlx_init()))
		return (errors_mlx("mlx_init()", 0, m_i));
	if (!((*m_i)->mlx_win = mlx_new_window((*m_i)->mlx_ptr, WIDTH,
					HEIGHT, "FDF")))
		return (errors_mlx("mlx_new_window()", 1, m_i));
	return (1);
}

void	calculate_dst_two_points(t_data **mai)
{
	(*mai)->dst_x = (WIDTH / 2) / (*mai)->nb_column;
	(*mai)->dst_y = (HEIGHT / 2) / (*mai)->nb_row;
}

int		draw_line(t_data **mai, size_t cur_x, size_t cur_y)
{
	size_t		cur_pix;
	size_t		end;

	cur_pix = cur_x * (*mai)->dst_x;
	end = (cur_pix + 1) * (*mai)->dst_x;
	while (cur_pix < end)
	{
		if (cur_pix > WIDTH * HEIGHT)
			((*mai)->mlx_data->img_add)[cur_pix * cur_y] = 0x000FFF;
		cur_pix++;
	}
	return (1);
}

int		draw_map(t_data **mai, t_mlx **m_i)
{
	size_t		i;
	int			add_p;

	calculate_dst_two_points(mai);
	i = 0;
	(*m_i)->mlx_img = mlx_new_image((*m_i)->mlx_ptr, WIDTH, HEIGHT);
	(*m_i)->img_add = (int*)mlx_get_data_addr((*m_i)->mlx_img,
			&add_p, &add_p, &add_p);
	while (i < (*mai)->nb_column - 1)
	{
		draw_line(mai, i, i * 20 + 1);
		i++;
	}
	mlx_put_image_to_window((*m_i)->mlx_ptr, (*m_i)->mlx_win, (*m_i)->mlx_img,
			0, 0);
	return (0);
}

int		main(int ac, char **av)
{
	t_data		*maps_info;

	if (ac == 1)
		return (usage_error_msg());
	maps_info = (t_data *)malloc(sizeof(t_data));
	maps_info->mlx_data = (t_mlx *)malloc(sizeof(t_mlx));
	if (read_file(&maps_info, av[1]) && mlx_starting(&(maps_info->mlx_data)))
	{
		if (!(draw_map(&maps_info, &(maps_info->mlx_data))))
			return (-1);
	}
	else
		return (-1);
	mlx_loop(maps_info->mlx_data->mlx_ptr);
	return (0);
}
