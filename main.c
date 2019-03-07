/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 23:24:51 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/07 15:33:07 by gvirga           ###   ########.fr       */
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

int		mlx_starting()
{
	t_mlx		m_i;

	m_i.
}

int		starting_with_the_basics()
{
	
	return (0);
}

int		main(int ac, char **av)
{
	if (ac == 1)
		return (error_msg(2));
	if (mlx_starting())
	{
	
	}
	return (0);
}
