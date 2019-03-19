/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 03:26:29 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/19 03:27:54 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		show_z_arr(t_data **maps_info)
{
	int		i;

	i = -1;
	while (++i < (*maps_info)->nb_of_elems)
	{
		ft_putnbr(((*maps_info)->z_arr)[i]);
		if (i != 0 && (i + 1) % (*maps_info)->nb_column == 0)
			ft_putchar('\n');
	}
}
