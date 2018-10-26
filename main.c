/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:14:43 by gvirga            #+#    #+#             */
/*   Updated: 2018/10/26 18:05:10 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./gnl/get_next_line.h"
#include <stdio.h>

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
	char	*line;
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
	// Etape 1 Verification du fichier
	if (!(mlx_ptr = mlx_init()))
		return (-1);
	if (!(mlx_win = mlx_new_window(mlx_ptr, 1280, 900, "42")))
		return (-1);
	nb_line = 0;
	str = ft_strnew(0);
	fd = open("./maps/basictest.fdf", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		nb_line++;
		tmp = str;
		str = ft_strjoin_free(tmp, line, 3);
		line = NULL;
	}
	close(fd);
	if (ret == -1)
		return (-1);
	//Etape 2 Transformation de la map en int
	if (!(map_final = (int**)malloc(sizeof(**map_final) * nb_line)))
		return (-1);
	len_line = ft_wordcount(str, ' ') / nb_line;
	i = 0;
	x = 0;
	while (i < nb_line)
	{
		int y = 0;
		if (!(numbers_of_current_line = ft_strsplit(str, ' ')))
				return (-1);
		if (!(map_final[i] = (int*)malloc(sizeof(*map_final) * len_line)))
			return (-1);
		while (y < len_line && numbers_of_current_line[x])
		{
			printf("numbers_of_current_line: %s\n", numbers_of_current_line[x]);
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

	current_line = 0;
	// Afficher l'axe x
	x = (1280 / len_line) - 10;
	y = (900 / nb_line) - 10;
	while (current_line < nb_line)
	{
		i = 0;
		while (i < len_line)
		{
			distance_x = 0;
			while (distance_x < x && i != len_line - 1)
			{
				mlx_pixel_put(mlx_ptr, mlx_win, (x * (i + 1)) + distance_x, (y * (current_line + 1)), 0xFFFFFF);
				distance_x++;
			}
			distance_y = 1;
			while (distance_y < y && current_line != nb_line - 1)
			{
				mlx_pixel_put(mlx_ptr, mlx_win, (x * (i + 1)), (y * (current_line + 1)) + distance_y, 0xFFFFFF);
				distance_y++;
			}
			i++;
		}
		current_line++;
	}

	mlx_key_hook(mlx_win, &deal_key, NULL);
	mlx_loop(mlx_ptr);
	return (0);
}
