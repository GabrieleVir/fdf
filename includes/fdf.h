/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 07:09:57 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/08 18:07:42 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFF_SIZE 1000
# define WIDTH 1920
# define HEIGHT 1080

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

typedef struct				s_file
{
	int						fd;
	int						ret;
	char					buf[BUFF_SIZE + 1];
}							t_file;

typedef struct				s_mlx
{
	void					*mlx_ptr;
	void					*mlx_win;
	int						*mlx_img;
	int						*img_add;
	int						add_p;
}							t_mlx;

typedef struct				s_data
{
	size_t					nb_column;
	size_t					nb_row;
	size_t					nb_of_elems;
	char					*data;
	intmax_t				biggest_z;
	intmax_t				*trans_map;
	size_t					dst_x;
	size_t					dst_y;
	size_t					dst_z;
	size_t					i;
	t_mlx					*mlx_data;
}							t_data;

typedef struct				s_bres
{
	int						width;
	int						height;
	int						x1;
	int						x2;
	int						y1;
	int						y2;
	int						dx1;
	int						dx2;
	int						dy1;
	int						dy2;
	int						long_dst;
	int						shrt_dst;
	int						numerator;
}							t_bres;

/*
** mlx functions
*/
int							starting_with_the_basics();
/*
** read file functions
*/
int							read_file(t_data **maps_info, char *file_name);
/*
** errors functions
*/
int							error_msg(int error);
int							usage_error_msg();
int							length_error_msg();
int							errors_mlx(char *fct_name_error, int frees,
							t_mlx **m_i);
int							error_file_msg(int error, t_data **maps_info);
int							error_empty_file(t_data **maps_info);
/*
** Map drawing functions
*/
int							draw_map(t_data **mai, t_mlx **m_i);
/*
** Bresenham algo functions
*/
void						draw_line(t_data **mai, t_bres *data);

#endif
