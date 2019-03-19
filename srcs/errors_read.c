/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:21:44 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/19 03:00:16 by gvirga           ###   ########.fr       */
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
	return (0);
}

int		usage_error_msg(void)
{
	ft_putstr("Usage: ./fdf <filename>\n");
	return (0);
}

int		length_error_msg(char ***tmp_map, t_data **maps_info)
{
	size_t		i;

	i = 0;
	while (i < (*maps_info)->nb_row)
	{
		free((*tmp_map)[i]);
		i++;
	}
	free(*tmp_map);
	free((*maps_info)->z_arr);
	ft_putstr("Found wrong line length. Exiting\n");
	return (0);
}

int		error_file_msg(int error, t_data **maps_info)
{
	char	*str;

	free((*maps_info)->data);
	ft_putstr("Error: ");
	str = strerror(error);
	ft_putstr(str);
	ft_putchar('\n');
	free(str);
	return (0);
}

int		error_empty_file(t_data **maps_info)
{
	free((*maps_info)->data);
	ft_putstr("No data found.\n");
	return (0);
}
