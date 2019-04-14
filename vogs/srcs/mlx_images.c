/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:03:04 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 03:36:10 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mlx_create_image(t_mlx **m_i)
{
	if (!((*m_i)->mlx_img = mlx_new_image((*m_i)->mlx_ptr, WIDTH, HEIGHT)))
		return (errors_mlx("mlx_new_image()", 0, m_i));
	if (!((*m_i)->img_add = (int*)mlx_get_data_addr((*m_i)->mlx_img,
			&((*m_i)->add_p), &((*m_i)->add_p), &((*m_i)->add_p))))
		return (errors_mlx("mlx_get_data_addr()", 0, m_i));
	return (1);
}
