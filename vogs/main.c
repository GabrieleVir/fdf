/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 23:24:51 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 05:55:41 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mlx_starting(t_mlx **m_i)
{
	if (!((*m_i)->mlx_ptr = mlx_init()))
		return (errors_mlx("mlx_init()", 0, m_i));
	if (!((*m_i)->mlx_win = mlx_new_window((*m_i)->mlx_ptr, WIDTH,
					HEIGHT, "FDF")))
		return (errors_mlx("mlx_new_window()", 1, m_i));
	return (1);
}

int		maps_info_malloc(t_data **maps_info)
{
	if (!((*maps_info) = (t_data *)malloc(sizeof(t_data))))
		return (error_msg(12));
	if (!((*maps_info)->mlx_data = (t_mlx *)malloc(sizeof(t_mlx))))
	{
		free(*maps_info);
		return (error_msg(12));
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_data		*maps_info;

	if (ac == 1)
		return (usage_error_msg());
	if (!(maps_info_malloc(&maps_info)))
		return (0);
	if (read_file(&maps_info, av[1]) && mlx_starting(&(maps_info->mlx_data)))
	{
		if (!(draw_map(&maps_info, &(maps_info->mlx_data))))
			return (-1);
	}
	else
		return (-1);
	options_fdf(&maps_info, &(maps_info->mlx_data));
	mlx_loop(maps_info->mlx_data->mlx_ptr);
	return (0);
}
