/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:11:34 by gvirga            #+#    #+#             */
/*   Updated: 2018/11/05 16:59:12 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include <math.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 900

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


	curr_y = (*coords).y0;
	curr_x = (*coords).x0;
	(*coords).dy2 = 0;
	(*coords).width = (*coords).x1 - (*coords).x0;
	(*coords).height = (*coords).y1 - (*coords).y0;
	(*coords).width < 0 ? ((*coords).dx1 = -1) : ((*coords).dx1 = 1);
	(*coords).height < 0 ? ((*coords).dy1 = -1) : ((*coords).dy1 = 1);
	(*coords).width < 0 ? ((*coords).dx2 = -1) : ((*coords).dx2 = 1);
	(*coords).width_size = (int)fabs((double)(*coords).width);
	(*coords).height_size = (int)fabs((double)(*coords).height);
	if ((*coords).width_size < (*coords).height_size)
	{
		(*coords).width_size = (int)fabs((double)(*coords).height);
		(*coords).height_size = (int)fabs((double)(*coords).width);
		(*coords).dx2 = 0;
		(*coords).height < 0 ? ((*coords).dy2 = -1) : ((*coords).dy2 = 1);
	}
	(*coords).error_margin = (*coords).width_size >> 1;
	i = -1;
	while (++i <= (*coords).width_size)
	{
		my_image_string[(curr_y * WIN_WIDTH) + curr_x] = 0x00FF00;
		printf("size my_image_string: %d \n", ((curr_y * WIN_WIDTH) + curr_x));
		printf("curr_x: %d \n", curr_y);
		printf("curr_y %d \n", curr_x);
		printf("WIN_WIDTH %d \n", WIN_WIDTH);
		(*coords).error_margin += (*coords).height_size;
		if ((*coords).error_margin >= (*coords).width_size)
		{
			(*coords).error_margin -= (*coords).width_size;
			curr_y += (*coords).dy1;
			curr_x += (*coords).dx1;
		}
		else
		{
			printf("(*coords).dx2: %d\n", (*coords).dx2);
			curr_x += (*coords).dx2;
			curr_y += (*coords).dy2;
		}
	}
}

int		main(void)
{
	int		map[5][5] = 
	{
		{1, 1, 1, 1, 1},
		{1, 5, 1, 2, 3},
		{1, 1, 1, 2, 3},
		{1, 2, 1, 2, 1},
		{1, 1, 1, 1, 1}
	};
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		display_size[2];
	int		i;
	int		y;
	int		starting_x;
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
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, display_size[0], display_size[1], "Testing");
	img_ptr = mlx_new_image(mlx_ptr, display_size[0], display_size[1]);
	// Obtention de la string que represent l'image
	my_image_string = (int*)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	// I can draw in this block
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2) + 100;
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2) - 100;
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2 + 100;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2);
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2 - 100;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2);
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2 - 100;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2) - 100;
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2 + 100;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2) + 100;
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2 + 100;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2) - 100;
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2 - 100;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2) + 100;
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
	coords.x0 = WIN_WIDTH / 2;
	coords.x1 = WIN_WIDTH / 2 - 150;
	coords.y0 = WIN_HEIGHT / 2;
	coords.y1 = (WIN_HEIGHT / 2) + 100;
	coords.dx1 = coords.x0 - coords.x1;
	coords.dy1 = coords.y0 - coords.y1;
	draw_line(&coords, my_image_string);
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
