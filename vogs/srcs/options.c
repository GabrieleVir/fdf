/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:23:00 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/10 04:41:07 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		options_fdf(t_data **mi, t_mlx **mlx)
{
	mlx_key_hook((*mlx)->mlx_win, &deal_key, mi);
	mlx_mouse_hook((*mlx)->mlx_win, &change_height, mi);
}
