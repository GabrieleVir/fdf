/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:11:34 by gvirga            #+#    #+#             */
/*   Updated: 2018/11/07 15:04:31 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
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

int		esc_key(int key, void *param)
{
	if (key == 53)
		exit(1);
	return (1);
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
		if ((pixel_pos >= 0 && pixel_pos < WIN_WIDTH * WIN_HEIGHT) && curr_x <= WIN_WIDTH && curr_x > 0 && curr_y > 0 && curr_y <= WIN_HEIGHT)
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

int		main(void)
{
	int		map[20][20] = 
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
		{0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
		{0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int		**trans_map;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		display_size[2];
	int		i;
	int		u;
	int		y;
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	int		starting_y;
	int		bpp;
	int		size_line;
	int		endian;
	int		*my_image_string;
	int		nb_of_columns;
	int		nb_of_lines;
	t_coord	coords;

	y = -1;
	i = -1;
	display_size[0] = WIN_WIDTH;
	display_size[1] = WIN_HEIGHT;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, display_size[0], display_size[1], "Testing");
	img_ptr = mlx_new_image(mlx_ptr, display_size[0], display_size[1]);
	// Obtention de la string que represente l'image
	my_image_string = (int*)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	// I can draw in this block
	nb_of_columns = 20;
	nb_of_lines = 20;
	//perc_wscreen = WIN_WIDTH / (nb_of_columns + max_height + 1);
	//margin_wscreen = WIN_WIDTH / nb_of_columns << 1;
	//perc_hscreen = WIN_HEIGHT / nb_of_lines;
	//margin_hscreen = WIN_HEIGHT / nb_of_lines << 1;
	trans_map = (int**)malloc(sizeof(int*) * 400);
	int z;
	while (++i < nb_of_columns * nb_of_lines)
	{
		z = map[i / nb_of_lines][i % nb_of_columns];
		trans_map[i] = (int*)malloc(sizeof(int) * 3);
		trans_map[i][0] = i % nb_of_columns - (z * 2);
		trans_map[i][1] = i / nb_of_lines + ((z - 1) / 100);
		trans_map[i][2] = z;
		printf("trans_map[%d][0]: %d trans_map[%d][1]: %d\n", i, trans_map[i][0], i, trans_map[i][1]);
	}
	int	distance;
	int	max_height;
	max_height = 10;
	distance = WIN_WIDTH / (nb_of_columns + nb_of_lines * 2);
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
				coords.x0 = (x0 * distance) + WIN_WIDTH/2;
				coords.x1 = (x1 * distance) + WIN_WIDTH/2;
				coords.y0 = (y0 * distance) + WIN_HEIGHT/2;
				coords.y1 = (y1 * distance) + WIN_HEIGHT/2;
				coords.color = trans_map[u + (i * nb_of_columns) + 1][2] - trans_map[u + (i * nb_of_columns)][2];
				coords.z0 = trans_map[u + (i * nb_of_columns)][2];
				coords.z1 = trans_map[u + (i * nb_of_columns) + 1][2];
				printf(" %d %d %d %d %d %d %d %d\n", x0, x1, y0, y1, coords.x0, coords.y0, coords.x1, coords.y1);
				draw_line(&coords, my_image_string);
			}
			// ligne entre le point et le point en dessous
			if (i + 1 != nb_of_lines && u != nb_of_columns)
			{
				x1 = trans_map[u + ((i + 1) * nb_of_lines)][0];
				y0 = trans_map[u + (i * nb_of_lines)][1];
				x0 = trans_map[u + (i * nb_of_lines)][0];
				y1 = trans_map[u + ((i + 1) * nb_of_lines)][1];
				coords.x0 = (x0 * distance) + WIN_WIDTH/2;
				coords.x1 = (x1 * distance) + WIN_WIDTH/2;
				coords.y0 = (y0 * distance) + WIN_HEIGHT/2;
				coords.y1 = (y1 * distance) + WIN_HEIGHT/2;
				coords.color = trans_map[u + ((i + 1) * nb_of_columns)][2] - trans_map[u + (i * nb_of_columns)][2];
				coords.z0 = trans_map[u + (i * nb_of_columns)][2];
				coords.z1 = trans_map[u + ((i + 1) * nb_of_columns)][2];
				draw_line(&coords, my_image_string);
			}
		}
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
/*
	while (++y < 1)
	{
		starting_y = (900 / 5) - 50 + (y * 100);
		i = -1;
		while (++i < 1)
		{
			starting_x = (1280 / 5) - 50 + (i * 100) + (y * 100);
			draw_line(map[0][0], map[0][1], starting_x, starting_y, starting_x + 100, starting_y, my_image_string);
			draw_line(map[0][0], map[0][1], starting_x, starting_y, starting_x + 100, starting_y + 100, my_image_string);
			draw_line(map[0][0], map[0][1], starting_x + 100, starting_y, starting_x + 200, starting_y + 100, my_image_string);
			draw_line(map[0][0], map[0][1], starting_x + 100, starting_y + 100, starting_x + 200, starting_y + 100, my_image_string);
		}
	}
*/
/*	while (++y < 2)
	{
		starting_y = ((900 / 5) - 33) + (y * 100);
		printf("starting_y: %d\n", starting_y);
		while (++i < 2)
		{
			starting_x = ((1280 / 5) - 33) + (i * 100);
		}
	}*/
	// end draw block
	// Adding esc key to exit window
	mlx_key_hook(win_ptr, &esc_key, NULL);
	mlx_loop(mlx_ptr);
}
