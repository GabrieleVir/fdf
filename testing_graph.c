/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:11:34 by gvirga            #+#    #+#             */
/*   Updated: 2018/10/29 22:06:06 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include <math.h>

int		esc_key(int key, void *param)
{
	if (key == 53)
		exit(1);
	return (1);
}

void	draw_line(int z0, int z1, int x0, int y0, int x1, int y1, int *my_image_string)
{
	int		dx;
	int		dy;
	int		dz;
	int		x;
	int		y;
	int		p;

	x = x0;
	y = y0;
	dx = x1 - x0;
	dy = y1 - y0;
	dz = z1 - z0;
	p = 2*dy - dx;
	
	while (x < x1)
	{
		if (p >= 0)
		{
			my_image_string[y * 1280 + x] = 0x00FFFFFF;
			y++;
			p = p + (2 * dy) - (2 * dx);
		}
		else
		{
			my_image_string[y * 1280 + x] = 0x00FFFF00;
			p = p + (2 * dy);
		}
		x++;
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

	y = -1;
	i = -1;
	display_size[0] = 1280;
	display_size[1] = 900;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, display_size[0], display_size[1], "Testing");
	img_ptr = mlx_new_image(mlx_ptr, display_size[0], display_size[1]);
	// Obtention de la string que represent l'image
	my_image_string = (int*)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	// I can draw in this block
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
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
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
