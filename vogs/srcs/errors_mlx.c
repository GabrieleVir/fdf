/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 01:49:05 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/08 19:30:53 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Errors when I manage the mlx functions
*/
#include "fdf.h"

int			errors_mlx(char *fct_name_error, int frees, t_mlx **m_i)
{
	if (frees == 1)
		free((*m_i)->mlx_ptr);
	ft_putstr("Error: ");
	ft_putstr("The function ");
	ft_putstr(fct_name_error);
	ft_putstr(" didn't succeed\n");
	return (0);
}
