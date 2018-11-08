/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:14:43 by gvirga            #+#    #+#             */
/*   Updated: 2018/11/08 15:10:07 by gvirga           ###   ########.fr       */
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

}						t_mlx;

/*
 ** Two gnl for : 
 ** 1) verification and number of lines.
 ** 2) putting every line in a array of array.
 */

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


int		main(void)
{
	t_mlx	*mlx_data;
	int		x = -1;
	int		y = -1;
	char	line[BUFF_SIZE + 1];
	int		fd;
	char 	**map;
	int		**map_final;
	int		nb_of_lines;
	int		i;
	int		nb_of_columns;
	char	**numbers_of_current_line;
	int		ret;
	char	*str;
	char	*tmp;
	char	**tmp1;
	// Etape 1 Verification du fichier
	mlx_data = (t_mlx*)malloc(sizeof(t_mlx));
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, mlx_data.win_width,
			mlx_data.win_height, "42");
	if (!(win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "42")))
		return (-1);
	nb_of_lines = 0;
	str = ft_strnew(0);
	fd = open("./maps/42.fdf", O_RDONLY);
	while ((ret = read(fd, line, BUFF_SIZE)) > 0)
	{
		line[ret] = '\0';
		tmp = str;
		str = ft_strjoin_free(tmp, line, 1);
	}
	close(fd);
	nb_of_lines = ft_wordcount(str, '\n');
	if (ret == -1)
		return (-1);
	//Etape 2 Transformation de la map en int
	if (!(map_final = (int**)malloc(sizeof(int*) * nb_of_lines)))
		return (-1);
	nb_of_columns = ft_wordcount2(str, ' ', '\n') / nb_of_lines;
	i = 0;
	x = 0;
	while (i < nb_of_lines)
	{
		y = 0;
		if (!(numbers_of_current_line = ft_strsplit2(str, ' ', '\n')))
			return (-1);
		if (!(map_final[i] = (int*)malloc(sizeof(int) * nb_of_columns)))
			return (-1);
		while (y < nb_of_columns && numbers_of_current_line[x])
		{
			map_final[i][y] = ft_atoi(numbers_of_current_line[x]);
			y++;
			x++;
		}
		i++;
	}

	int		**trans_map;
	void	*img_ptr;
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
	display_size[0] = WIN_WIDTH;
	display_size[1] = WIN_HEIGHT;
	img_ptr = mlx_new_image(mlx_ptr, display_size[0], display_size[1]);
	// Obtention de la string que represente l'image
	my_image_string = (int*)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	trans_map = (int**)malloc(sizeof(int*) * nb_of_columns * nb_of_lines);
	int z;
	while (++i < nb_of_lines)
	{
		u = -1;
		while (++u < nb_of_columns)
		{
			z = map_final[i][u];
			trans_map[(i * nb_of_columns) + u] = (int*)malloc(sizeof(int) * 3);
			trans_map[(i * nb_of_columns) + u][0] = (u - (z / 2));
			trans_map[(i * nb_of_columns) + u][1] = i - ((z + 1)*2);
			trans_map[(i * nb_of_columns) + u][2] = z;
		}
	}
	int	distance;
	int	max_height;
	max_height = 10;
	distance = WIN_WIDTH / (nb_of_columns * nb_of_lines / 2);
	i = -1;
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
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_mouse_hook(win_ptr, &mouse_key, my_image_string);
	mlx_key_hook(win_ptr, &deal_key, NULL);
	mlx_loop(mlx_ptr);
	return (0);
}
