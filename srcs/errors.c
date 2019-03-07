/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:21:44 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/07 21:02:39 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		error_msg(int error)
{
	char	*str;

	ft_putstr("Error: ");
	str = strerror(error);
	ft_putstr(str);
	ft_putchar('\n');
	free(str);
	return (-1);
}

int		usage_error_msg()
{
	ft_putstr("Usage: ./fdf <filename>\n");
	return (-1);
}
