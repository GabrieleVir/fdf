/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:14:43 by gvirga            #+#    #+#             */
/*   Updated: 2018/11/18 03:04:22 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <math.h>

#define WIN_WIDTH 5000
#define WIN_HEIGHT 4000

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
	int		lowest_color;
	int		highest_color;
	int		highest_point;
	int		lowest_point;
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
	int					distance_z;
	int					*default_map;
	int					*trans_map;
	int					highest_point;
	int					lowest_point;
}						t_map;

typedef struct			s_params
{
	t_map				*maps;
	t_mlx				*mlx_data;
}						t_params;

int		move_trans_map(t_map **map, int direction)
{
	int		i;

	i = -1;
	if (direction == 0)
		while (++i < (*map)->columns * (*map)->lines)
			(*map)->trans_map[i * 3] -= 100;
	else if (direction == 2)
		while (++i < (*map)->columns * (*map)->lines)
			(*map)->trans_map[i * 3 + 1] += 100;
	else if (direction == 1)
		while (++i < (*map)->columns * (*map)->lines)
			(*map)->trans_map[i * 3] += 100;
	else
	{
		while (++i < (*map)->columns * (*map)->lines)
			(*map)->trans_map[i * 3 + 1] -= 100;
	}	
	return(1);
}

int		move_z_value(t_map **map, int direction)
{
	int		i;
	int		z0;
	int		z1;

	i = -1;
	while (++i < (*map)->columns * (*map)->lines)
	{
		z0 = (*map)->default_map[i] * (*map)->distance_z;
		if (direction == 0)
			(*map)->distance_z -= 1;
		else
			(*map)->distance_z += 1;
		z1 = (*map)->default_map[i] * (*map)->distance_z;
		(*map)->trans_map[i * 3 + 1] += (z0 - z1);
	}
	return(1);
}

/*
 ** This manage all the octants, the magic is in the initiation of dx1 and dy1
 ** Need to add limits
 */

void	draw_line(t_coord *coords, int *my_image_string, int win_width, int win_height)
{
	int		i;
	int		curr_x;
	int		curr_y;
	int		pixel_pos;
	int		color;

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
	(*coords).lowest_color = 0xFFFFFF;
	(*coords).highest_color = 0x0000FF;
	while (++i <= (*coords).width_size)
	{
		pixel_pos = (int)(curr_y * WIN_WIDTH + curr_x);
		if ((pixel_pos >= 0 && pixel_pos < WIN_WIDTH * WIN_HEIGHT) && curr_x < WIN_WIDTH && curr_x > 0 && curr_y > 0 && curr_y < WIN_HEIGHT)
		{
			if ((*coords).z0 != (*coords).lowest_point || (*coords).z0 != (*coords).highest_point)
				color = (*coords).highest_color + (((*coords).highest_point - (*coords).z0) * 256);  
			else
				color = 0xFFFFFF;
			if (color < 0x0000FF)
				color = 0xFFFFFF;
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

int		redraw_map(t_mlx **mlx_data, t_map *maps)
{
	int		i;
	int		starting_y;
	int		bpp;
	int		size_line;
	int		endian;
	int		*my_image_string;
	t_coord	coords;

	mlx_destroy_image((*mlx_data)->mlx_ptr, (*mlx_data)->img_ptr);
	i = -1;
	(*mlx_data)->img_ptr = mlx_new_image((*mlx_data)->mlx_ptr, (*mlx_data)->win_width, (*mlx_data)->win_height);
	my_image_string = (int*)mlx_get_data_addr((*mlx_data)->img_ptr, &bpp, &size_line, &endian);
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
			coords.highest_point = maps->highest_point;
			coords.lowest_point = maps->lowest_point;
			draw_line(&coords, my_image_string, (*mlx_data)->win_width, (*mlx_data)->win_height);
		}
		if (i + maps->columns < maps->columns * maps->lines)
		{
			coords.x0 = maps->trans_map[i * 3];
			coords.x1 = maps->trans_map[(i + maps->columns) * 3];
			coords.y0 = maps->trans_map[i * 3 + 1];
			coords.y1 = maps->trans_map[(i + maps->columns) * 3 + 1];
			coords.z0 = maps->trans_map[i * 3 + 2];
			coords.z1 = maps->trans_map[(i + maps->columns) * 3 + 2];
			coords.highest_point = maps->highest_point;
			coords.lowest_point = maps->lowest_point;
			draw_line(&coords, my_image_string, (*mlx_data)->win_width, (*mlx_data)->win_height);
		}
	}
	mlx_put_image_to_window((*mlx_data)->mlx_ptr, (*mlx_data)->win_ptr, (*mlx_data)->img_ptr, 0, 0);	
	return (1);
}

int		deal_key(int key, t_params *params)
{
	t_map	*maps;
	t_mlx	*mlx_data;

	maps = params->maps;
	mlx_data = params->mlx_data;
	if (key == 53)
		exit(1);
	else if (key >= 123 && key <= 126)
	{
		move_trans_map(&maps, key - 123);
		redraw_map(&mlx_data, maps);
	}
	return (0);
}

int		change_height(int key, int x, int y, t_params *params)
{
	t_map	*maps;
	t_mlx	*mlx_data;

	x = y;
	maps = params->maps;
	mlx_data = params->mlx_data;
	if (key == 4 || key == 5)
	{
		move_z_value(&maps, key - 4);
		redraw_map(&mlx_data, maps);
	}
	return (0);
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
		mlx_data->s_v2[0] = x;
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

int		*fill_map(int nb_of_lines, int nb_of_columns, char *str, t_map **maps)
{
	int		*default_map;
	int		i;
	char	**nbs_in_map;

	i = -1;
	default_map = (int*)malloc(sizeof(int) * nb_of_lines * nb_of_columns);
	if (!default_map)
		return (NULL);
	(*maps)->highest_point = 0;
	(*maps)->lowest_point = 0;
	if (!(nbs_in_map = ft_strsplit2(str, ' ', '\n')))
		return (NULL);
	while (++i < nb_of_columns * nb_of_lines)
	{
		default_map[i] = ft_atoi(nbs_in_map[i]);
		free(nbs_in_map[i]);
		if ((*maps)->highest_point < default_map[i])
			(*maps)->highest_point = default_map[i];
		if ((*maps)->lowest_point > default_map[i])
			(*maps)->lowest_point = default_map[i];
	}
	free(nbs_in_map);
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
		if (!(*str = ft_strjoin_free(tmp, line, 1)))
			return (error_mng_var("*str", "NULL"));
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
		fill_map((*maps)->lines, (*maps)->columns, str, maps)))
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

int			trans_map(t_map **maps, int width, int height)
{
	int		i;
	int		lines;
	int		columns;
	int		x;
	int		y;
	int		z;
	int		dz;

	dz = (*maps)->highest_point - (*maps)->lowest_point;
	lines = (*maps)->lines;
	columns = (*maps)->columns;
	i = -1;
	if (((*maps)->distance_x = width / (columns * 4)) < 10)
		(*maps)->distance_x = 5;
	if (((*maps)->distance_y = height / (lines * 4)) < 10)
		(*maps)->distance_y = 5;
	if (((*maps)->highest_point + (*maps)->lowest_point) > (*maps)->distance_y)
		(*maps)->distance_z = 5;
	else
		(*maps)->distance_z = 10;
	if (!((*maps)->trans_map = (int*)malloc(sizeof(int) * lines * columns * 3)))
		return (error_management("trans_map", "malloc"));
	while (++i < lines * columns)
	{
		x = i % columns * (*maps)->distance_x;
		y = i / columns * (*maps)->distance_y;
		z = (*maps)->default_map[i] * (*maps)->distance_z;
		(*maps)->trans_map[i * 3] = x * cos(0.523599) - y * cos(0.523599);
		(*maps)->trans_map[i * 3 + 1] = x * sin(0.523599) + y * sin(0.523599) - z;
		(*maps)->trans_map[i * 3 + 2] = z;
	}
	return (1);
}

void		coords_x_axis(t_coord *coords, t_map *maps, int i)
{
	(*coords).x0 = maps->trans_map[i * 3];
	(*coords).x1 = maps->trans_map[(i + 1) * 3];
	(*coords).y0 = maps->trans_map[i * 3 + 1];
	(*coords).y1 = maps->trans_map[(i + 1) * 3 + 1];
	(*coords).z0 = maps->trans_map[i * 3 + 2];
	(*coords).z1 = maps->trans_map[(i + 1) * 3 + 2];
}

void		coords_y_axis(t_coord *coords, t_map *maps, int i)
{
	(*coords).x0 = maps->trans_map[i * 3];
	(*coords).x1 = maps->trans_map[(i + maps->columns) * 3];
	(*coords).y0 = maps->trans_map[i * 3 + 1];
	(*coords).y1 = maps->trans_map[(i + maps->columns) * 3 + 1];
	(*coords).z0 = maps->trans_map[i * 3 + 2];
	(*coords).z1 = maps->trans_map[(i + maps->columns) * 3 + 2];
}

/*
**	The coordinations changed when we are drawing a line between two points from
**	the x axis or a line between two points from the y axis
*/
int			draw_map(t_mlx **mlx_data, t_map *maps)
{
	int		i;
	int		starting_y;
	int		bpp;
	int		size_line;
	int		endian;
	int		*my_image_string;
	t_coord	coords;

	i = -1;
	(*mlx_data)->img_ptr = mlx_new_image((*mlx_data)->mlx_ptr, (*mlx_data)->win_width, (*mlx_data)->win_height);
	// Obtention de la string que represente l'image
	my_image_string = (int*)mlx_get_data_addr((*mlx_data)->img_ptr, &bpp, &size_line, &endian);
	i = -1;
	coords.lowest_point = maps->lowest_point;
	coords.highest_point = maps->highest_point;
	while (++i < maps->lines * maps->columns)
	{
		if ((i + 1) % maps->columns != 0)
		{
			coords_x_axis(&coords, maps, i);
			draw_line(&coords, my_image_string, (*mlx_data)->win_width, (*mlx_data)->win_height);
		}
		if (i + maps->columns < maps->columns * maps->lines)
		{
			coords_y_axis(&coords, maps, i);
			draw_line(&coords, my_image_string, (*mlx_data)->win_width, (*mlx_data)->win_height);
		}
	}
	return (1);
}

int			init_fdf(t_mlx **mlx_data)
{
	if (!((*mlx_data) = (t_mlx*)malloc(sizeof(t_mlx))))
		return (error_management("mlx_data", "malloc"));
	if (!((*mlx_data)->mlx_ptr = mlx_init()))
		return (error_management("mlx_data->mlx_ptr", "mlx_init()"));
	(*mlx_data)->win_width = 5000;
	(*mlx_data)->win_height = 4000;
	if (!((*mlx_data)->win_ptr = mlx_new_window((*mlx_data)->mlx_ptr,
					(*mlx_data)->win_width, (*mlx_data)->win_height, "42")))
		return (error_management("mlx_data->win_ptr", "new_window()"));
	return (1);
}

int			init_maps(t_map **maps, char *path_file, t_mlx **mlx_data)
{
	if (!((*maps) = (t_map*)malloc(sizeof(t_map))))
		return (error_management("maps", "malloc"));
	if ((read_map(path_file, maps) < 0))
		return (error_management("default_map", "read_map()"));
	if (!(trans_map(maps, (*mlx_data)->win_width, (*mlx_data)->win_height)))
		return (error_management("trans_map", "trans_map()"));
	return (1);
}

int			error_mng_args(int ac)
{
	if (ac < 2)
		ft_putstr("To use fdf you need to give the path to the fdf file. Example: ./fdf maps/42.fdf");
	else
		ft_putstr("Fdf can manage only one file at the time.");
	return (-1);
}

int			error_mng_text(char *text)
{
	ft_putstr(text);
	return (-1);
}

int			render(t_mlx **mlx_data, t_map *maps)
{
	if ((draw_map(mlx_data, maps)) == -1)
		return (error_management("draw_map()", "drawing"));
	mlx_put_image_to_window((*mlx_data)->mlx_ptr,
		(*mlx_data)->win_ptr, (*mlx_data)->img_ptr, 0, 0);
	return (1);
}

int			main(int ac, char **av)
{
	t_mlx		*mlx_data;
	t_map		*maps;
	t_params	*params;

	if (ac != 2)
		return (error_mng_args(ac));
	// mlx initialisation of the mlx
	if ((init_fdf(&mlx_data)) == -1 || (init_maps(&maps, av[1], &mlx_data)) == -1)
		return (error_management("init_fdf() or init_map()", "initialisation"));
	if ((render(&mlx_data, maps)) == -1)
		return (error_mng_text("Something went wrong in the rendering"));
	params = (t_params*)malloc(sizeof(t_params));
	params->mlx_data = mlx_data;
	params->maps = maps;
	printf("params->maps: %p params->mlx_data: %p\n", params->maps, params->mlx_data);
	mlx_key_hook(mlx_data->win_ptr, &deal_key, params);
	mlx_mouse_hook(mlx_data->win_ptr, &change_height, params);
	mlx_loop(mlx_data->mlx_ptr);
	return (0);
}
