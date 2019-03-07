/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:23:15 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/07 21:13:19 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fill_info(t_data **maps_info)
{
	return (0);
}

int		read_file(t_data **maps_info, char *file_name)
{
	t_file		file;

	(*maps_info)->data = ft_strnew(0);
	if ((file.fd = open(file_name, O_RDONLY)) == -1)
		return (error_msg(2));
	while ((file.ret = read(file.fd, file.buf, BUFF_SIZE)) > 0)
	{
		(file.buf)[file.ret] = '\0';
		if (!((*maps_info)->data = ft_strjoin_free((*maps_info)->data,
					file.buf, 1)))
			return (error_msg(12));
	}
	if (file.ret < 0)
		return (error_msg(9));
	close(file.fd);
//	ft_putstr((*maps_info)->data);
	return (fill_info(maps_info));
}
