/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:14:43 by gvirga            #+#    #+#             */
/*   Updated: 2018/10/26 22:31:28 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./gnl/get_next_line.h"
#include <stdio.h>
#include <math.h>

/*
** Two gnl for : 
** 1) verification and number of lines.
** 2) putting every line in a array of array.
*/

int		deal_key(int key, void* param)
{
	if (key == 53)
		exit(1);
	return (1);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		x = -1;
	int		y = -1;
	char	line[BUFF_SIZE + 1];
	int		fd;
	char 	**map;
	int		**map_final;
	int		nb_line;
	int		i;
	int		len_line;
	char	**numbers_of_current_line;
	int		ret;
	char	*str;
	char	*tmp;
	char	**tmp1;
	// Etape 1 Verification du fichier
	if (!(mlx_ptr = mlx_init()))
		return (-1);
	if (!(mlx_win = mlx_new_window(mlx_ptr, 1280, 900, "42")))
		return (-1);
	nb_line = 0;
	str = ft_strnew(0);
	fd = open("./maps/basictest.fdf", O_RDONLY);
	while ((ret = read(fd, line, BUFF_SIZE)) > 0)
	{
		line[ret] = '\0';
		tmp = str;
		str = ft_strjoin_free(tmp, line, 1);
	}
	close(fd);
	nb_line = ft_wordcount(str, '\n');
	if (ret == -1)
		return (-1);
	//Etape 2 Transformation de la map en int
	if (!(map_final = (int**)malloc(sizeof(int*) * nb_line)))
		return (-1);
	len_line = ft_wordcount2(str, ' ', '\n') / nb_line;
	i = 0;
	x = 0;
	while (i < nb_line)
	{
		int y = 0;
		if (!(numbers_of_current_line = ft_strsplit2(str, ' ', '\n')))
				return (-1);
		if (!(map_final[i] = (int*)malloc(sizeof(int) * len_line)))
			return (-1);
		while (y < len_line && numbers_of_current_line[x])
		{
			map_final[i][y] = ft_atoi(numbers_of_current_line[x]);
			y++;
			x++;
		}
		i++;
	}
	i = -1;
	while (++i < nb_line)
	{
		y = 0;
		while (y < len_line)
		{
			ft_putnbr(map_final[i][y]);
			y++;
		}
		ft_putchar('\n');
	}
	
	int		distance_x;
	int		distance_y;
	int		current_line;
	int		decal_x;
	int		angle_inc_y;
	int		calc_x;
	int		position_x;

	current_line = 0;
	// Afficher l'axe x
	x = (1280 / len_line) - 66;
	y = (900 / nb_line) - 66;
	decal_x = 0;
	while (current_line < nb_line)
	{
		i = 0;
		while (i < len_line)
		{
			distance_x = 0;
			position_x = (x * (i + 1)) + 300 - (decal_x);
			while (distance_x < x && i < len_line - 1)
			{
				printf("%d\n", x*(i+1));
				calc_x = position_x + distance_x;
				printf("%d\n", calc_x);
				mlx_pixel_put(mlx_ptr, mlx_win, calc_x, 300 + (y * (current_line + 1)), 0xFFFFFF);
				distance_x++;
			}
			distance_y = 1;
			angle_inc_y = 0;
			while (distance_y < y && current_line < nb_line - 1)
			{
				mlx_pixel_put(mlx_ptr, mlx_win, (position_x - angle_inc_y), 300 + (y * (current_line + 1)) + distance_y, 0xFFFFFF);
				distance_y++;
				angle_inc_y++;
			}
			i++;
		}
		decal_x += angle_inc_y;
		current_line++;
	}

	mlx_key_hook(mlx_win, &deal_key, NULL);
	mlx_loop(mlx_ptr);
	return (0);
}
