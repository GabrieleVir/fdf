/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 23:24:51 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/17 17:28:51 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int		mlx_starting(t_mlx **m_i)
{
	(*m_i)->mlx_ptr = mlx_init();
	(*m_i)->mlx_img = mlx_new_image((*m_i)->mlx_ptr, WIDTH, HEIGHT);
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
		
	}
	else
		return (-1);
	return (0);
}
