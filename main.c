/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:14:43 by gvirga            #+#    #+#             */
/*   Updated: 2018/11/13 02:24:05 by gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./gnl/get_next_line.h"
#include <stdio.h>
#include <math.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

typedef struct			s_coord
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		dy1;
	int		dx1;
	int		dy2;
	int		dx2;
	int		error_margin;
	int		width_size;
	int		height_size;
	int		width;
	int		height;
	int		color;
	int		z0;
	int		z1;
}						t_coord;

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	int					win_width;
	int					win_height;
}						t_mlx;

typedef struct			s_map
{
	int					columns;
	int					lines;
	int					distance_x;
	int					distance_y;
	int					*default_map;
	int					*trans_map;
}						t_map;

int		deal_key(int key, void* param)
{
	if (key == 53)
		exit(1);
	return (0);
}

/*
 ** This manage all the octants, the magic is in the initiation of dx1 and dy1
 ** Need to add limits
 */

void	draw_line(t_coord *coords, int *my_image_string)
{
	int		i;
	int		curr_x;
	int		curr_y;
	int		pixel_pos;

	curr_y = (*coords).y0;
	curr_x = (*coords).x0;
	(*coords).dy2 = 0;
	(*coords).width = (*coords).x1 - (*coords).x0;
	(*coords).height = (*coords).y1 - (*coords).y0;
	(*coords).width < 0 ? ((*coords).dx1 = -1) : ((*coords).dx1 = 1);
	(*coords).height < 0 ? ((*coords).dy1 = -1) : ((*coords).dy1 = 1);
	(*coords).width < 0 ? ((*coords).dx2 = -1) : ((*coords).dx2 = 1);
	(*coords).width_size = fabs((double)(*coords).width);
	(*coords).height_size = fabs((double)(*coords).height);
	if ((*coords).width_size < (*coords).height_size)
	{
		(*coords).width_size = (int)fabs((double)(*coords).height);
		(*coords).height_size = (int)fabs((double)(*coords).width);
		(*coords).dx2 = 0;
		(*coords).height < 0 ? ((*coords).dy2 = -1) : ((*coords).dy2 = 1);
	}
	(*coords).error_margin = (*coords).width_size >> 1;
	i = -1;
	int color;
	while (++i <= (*coords).width_size)
	{
		pixel_pos = (int)(curr_y * WIN_WIDTH + curr_x);
		if ((pixel_pos >= 0 && pixel_pos < WIN_WIDTH * WIN_HEIGHT) && curr_x <= WIN_WIDTH && curr_x > 0 && curr_y > 0 && curr_y < WIN_HEIGHT)
		{
			if ((*coords).color >= 3)
				color = 0xFFFFFF;
			else if ((*coords).color < 0)
				color = 0xFFFFFF;
			else
			{
				if ((*coords).z0 >= 3)
					color = 0xFFFFFF;
				else if ((*coords).z0 < 0)
					color = 0x0000FF;
				else
					color = 0x00FF00;
			}
			my_image_string[pixel_pos] = color;
		}
		(*coords).error_margin += (*coords).height_size;
		if ((*coords).error_margin >= (*coords).width_size)
		{
			(*coords).error_margin -= (*coords).width_size;
			curr_y += (*coords).dy1;
			curr_x += (*coords).dx1;
		}
		else
		{
			curr_x += (*coords).dx2;
			curr_y += (*coords).dy2;
		}
	}
}
/*
int		mouse_key(int button, int x, int y, void *my_image_string)
{
	static int s_v2[2];
	int e_v2[2];
	t_coord coords;

	printf("button = %d\n", button);
	if (s_v2[0] == 0 && s_v2[1] == 0)
	{
		printf("line start: %i, %i\n", x, y);
		s_v2[0] = x;
		s_v2[1] = y;
	}
	else
	{
		printf("line end: %i, %i\n", x, y);
		e_v2[0] = x;
		e_v2[1] = y;
		coords.x0 = s_v2[0];
		coords.y0 = s_v2[1];
		coords.y1 = e_v2[1];
		coords.x1 = e_v2[0];
		coords.z0 = 0;
		coords.z1 = 0;
		draw_line(&coords, (int*)my_image_string);
		s_v2[0] = 0;
		s_v2[1] = 0;
	}
	return (1);
}
*/

int		error_management(char *var_name, char *reason)
{
	ft_putstr("The ");
	ft_putstr(reason);
	ft_putstr(" didn't work for the variable ");
	ft_putstr(var_name);
	ft_putchar('\n');
	return (-1);
}

int		error_mng_var(char *var_name, char *reason)
{
	ft_putstr("The ");
	ft_putstr(var_name);
	ft_putstr(" is set to ");
	ft_putstr(reason);
	ft_putchar('\n');
	return (-1);
}

int		*fill_map(int nb_of_lines, int nb_of_columns, char *str)
{
	int		*default_map;
	int		i;
	char	**nbs_of_map;

	i = -1;
	default_map = (int*)malloc(sizeof(int) * nb_of_lines * nb_of_columns);
	if (!default_map)
		return (NULL);
	if (!(nbs_of_map = ft_strsplit2(str, ' ', '\n')))
		return (NULL);
	while (++i < nb_of_columns * nb_of_lines)
	{
		default_map[i] = ft_atoi(nbs_of_map[i]);
		free(nbs_of_map[i]);
	}
	free(nbs_of_map);
	return (default_map);
}
int		read_file(char **str, char *path_file)
{
	int		fd;
	int		ret;
	char	line[BUFF_SIZE + 1];
	char	*tmp;

	fd = open(path_file, O_RDONLY);
	if (!(*str = ft_strnew(0)))
		return (error_mng_var("*str", "NULL"));
	while ((ret = read(fd, line, BUFF_SIZE)) > 0)
	{
		line[ret] = '\0';
		tmp = *str;
		*str = ft_strjoin_free(tmp, line, 1);
	}
	if (ret == -1)
		return (error_management("ret", "read()"));
	close(fd);
	return (1);
}

int		read_map(char *path_file, t_map **maps)
{
	char	*str;
	char	*tmp;

	if (!(read_file(&str, path_file)))
		return (-1);
	if (!((*maps)->lines = ft_wordcount(str, '\n')))
		return (error_mng_var("lines", "0"));
	if (!((*maps)->columns = ft_wordcount2(str, ' ', '\n') / (*maps)->lines))
		return (error_mng_var("columns", "0"));
	if (!((*maps)->default_map = 
		fill_map((*maps)->lines, (*maps)->columns, str)))
		return (error_mng_var("default_map", "NULL"));
	free(str);
	return (1);
}

/*
** With the variables win_width and win_height I can 
** calculate the distancex and distancey between each
** point, thanks to that, I ll be able to use cos and sin
** and get an approximation of a rotation in int.
** If the distance is set to a minimum in case the map is too big
** for the width and height of the mlx_window
*/

int		trans_map(t_map	**maps, int width, int height)
{
	int		i;
	int		lines;
	int		columns;
	int		x;
	int		y;
	int		z;

	lines = (*maps)->lines;
	columns = (*maps)->columns;
	i = -1;
	if (((*maps)->distance_x = width / (columns * 4)) < 10)
		(*maps)->distance_x = 10;
	if (((*maps)->distance_y = height / (lines * 4)) < 10)
		(*maps)->distance_y = 10;
	if (!((*maps)->trans_map = (int*)malloc(sizeof(int) * lines * columns * 3)))
		return (error_management("trans_map", "malloc"));
	while (++i < lines * columns)
	{
		x = i % columns * (*maps)->distance_x;
		y = i / columns * (*maps)->distance_y + 400;
		z = (*maps)->default_map[i] * (*maps)->distance_y;
		(*maps)->trans_map[i * 3] = x * cos(0.523599) + y * sin(0.523599) + z * sin(0.523599);
		(*maps)->trans_map[i * 3 + 1] = -(x * sin(0.523599)) + y * cos(0.523599) - z * cos(0.523599);
		(*maps)->trans_map[i * 3 + 2] = (*maps)->default_map[i];
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_mlx	*mlx_data;
	t_map	*maps;
	int		x = -1;
	int		y = -1;
	int		i;

	if (ac != 2)
		return (-1);
	// mlx initialisation of the mlx
	if (!(mlx_data = (t_mlx*)malloc(sizeof(t_mlx))))
		return (error_management("mlx_data", "malloc"));
	if (!(mlx_data->mlx_ptr = mlx_init()))
		return (error_management("mlx_data->mlx_ptr", "mlx_init()"));
	mlx_data->win_width = 1280;
	mlx_data->win_height = 720;
	if (!(mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr,
					mlx_data->win_width, mlx_data->win_height, "42")))
		return (error_management("mlx_data->win_ptr", "new_window()"));
	// Filling the =! types of map
	if (!(maps = (t_map*)malloc(sizeof(t_map))))
		return (error_management("maps", "malloc"));
	if (!(read_map(av[1], &maps)))
		return (error_management("default_map", "read_map()"));
	if (!(trans_map(&maps, mlx_data->win_width, mlx_data->win_height)))
		return (error_management("trans_map", "trans_map()"));
	int		display_size[2];
	int		u;
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	int		starting_y;
	int		bpp;
	int		size_line;
	int		endian;
	int		*my_image_string;
	t_coord	coords;

	y = -1;
	i = -1;
	display_size[0] = mlx_data->win_width;
	display_size[1] = mlx_data->win_height;
	mlx_data->img_ptr = mlx_new_image(mlx_data->mlx_ptr, display_size[0], display_size[1]);
	// Obtention de la string que represente l'image
	my_image_string = (int*)mlx_get_data_addr(mlx_data->img_ptr, &bpp, &size_line, &endian);
	i = -1;
	while (++i < maps->lines * maps->columns)
	{
		if ((i + 1) % maps->columns != 0)
		{
			coords.x0 = maps->trans_map[i * 3];
			coords.x1 = maps->trans_map[(i + 1) * 3];
			coords.y0 = maps->trans_map[i * 3 + 1];
			coords.y1 = maps->trans_map[(i + 1) * 3 + 1];
			coords.z0 = maps->trans_map[i * 3 + 2];
			coords.z1 = maps->trans_map[(i + 1) * 3 + 2];
			draw_line(&coords, my_image_string);
		}
		if (i + maps->columns < maps->columns * maps->lines)
		{
			coords.x0 = maps->trans_map[i * 3];
			coords.x1 = maps->trans_map[(i + maps->columns) * 3];
			coords.y0 = maps->trans_map[i * 3 + 1];
			coords.y1 = maps->trans_map[(i + maps->columns) * 3 + 1];
			coords.z0 = maps->trans_map[i * 3 + 2];
			coords.z1 = maps->trans_map[(i + maps->columns) * 3 + 2];
			draw_line(&coords, my_image_string);
		}
	}
	/*
	while (++i < nb_of_lines)
	{
		u = -1;
		while (++u < nb_of_columns)
		{
			// ligne entre le point avec le point a droite
			if (u + 1 != nb_of_columns)
			{
				x0 = trans_map[u + (i * nb_of_columns)][0];
				x1 = trans_map[u + (i * nb_of_columns) + 1][0];
				y0 = trans_map[u + (i * nb_of_columns)][1];
				y1 = trans_map[u + (i * nb_of_columns) + 1][1];
				coords.x0 = (x0 * distance) + 1 + (max_height * distance);
				coords.x1 = (x1 * distance) + 1 + (max_height * distance);
				coords.y0 = (y0 * distance) + WIN_HEIGHT - (nb_of_lines * distance) - (max_height * distance) - 1;
				coords.y1 = (y1 * distance) + WIN_HEIGHT - (nb_of_lines * distance) - (max_height * distance) - 1;
				coords.color = trans_map[u + (i * nb_of_columns) + 1][2] - trans_map[u + (i * nb_of_columns)][2];
				coords.z0 = trans_map[u + (i * nb_of_columns)][2];
				coords.z1 = trans_map[u + (i * nb_of_columns) + 1][2];
				draw_line(&coords, my_image_string);
			}
			// ligne entre le point et le point en dessous
			if (i + 1 != nb_of_lines && u != nb_of_columns)
			{
				x1 = trans_map[u + ((i + 1) * nb_of_columns)][0];
				y0 = trans_map[u + (i * nb_of_columns)][1];
				x0 = trans_map[u + (i * nb_of_columns)][0];
				y1 = trans_map[u + ((i + 1) * nb_of_columns)][1];
				coords.x0 = (x0 * distance) + 1 + (max_height * distance);
				coords.x1 = (x1 * distance) + 1 + (max_height * distance);
				coords.y0 = (y0 * distance) + WIN_HEIGHT - (nb_of_lines * distance) - (max_height * distance) - 1;
				coords.y1 = (y1 * distance) + WIN_HEIGHT - (nb_of_lines * distance) - (max_height * distance) - 1;
				coords.color = trans_map[u + ((i + 1) * nb_of_columns)][2] - trans_map[u + (i * nb_of_columns)][2];
				coords.z0 = trans_map[u + (i * nb_of_columns)][2];
				coords.z1 = trans_map[u + ((i + 1) * nb_of_columns)][2];
				draw_line(&coords, my_image_string);
			}
		}
	}*/
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
	//mlx_mouse_hook(win_ptr, &mouse_key, my_image_string);
	mlx_key_hook(mlx_data->win_ptr, &deal_key, NULL);
	mlx_loop(mlx_data->mlx_ptr);
	return (0);
}
