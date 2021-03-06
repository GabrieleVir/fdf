/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 07:09:57 by gvirga            #+#    #+#             */
/*   Updated: 2019/04/12 06:33:34 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFF_SIZE 100000
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
	intmax_t				highest_z;
	int						projection;
	int						highest_color;
	int						force_color;
	intmax_t				*trans_map;
	size_t					dst_x;
	size_t					dst_y;
	size_t					dst_z;
	intmax_t				pad_x;
	intmax_t				pad_y;
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
	intmax_t				z1;
	intmax_t				z2;
	int						dx1;
	int						dx2;
	int						dy1;
	int						dy2;
	int						long_dst;
	int						shrt_dst;
	int						numerator;
	int						end_color;
	int						start_color;
}							t_bres;

typedef struct				s_params
{
	t_data					*data;
}							t_params;

typedef struct				s_current
{
	int						curr_x;
	int						curr_y;
}							t_current;

/*
** mlx functions
*/
int							starting_with_the_basics();
int							mlx_create_image(t_mlx **m_i);
/*
** read file functions
*/
int							read_file(t_data **maps_info, char *file_name);
void						trans_map(t_data **mai, int first_prog_launch,
										int projection);
int							fill_z_arr(t_data **m_i, char *row, size_t i);
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
/*
** Linear gradient
*/
int							get_color(t_current current, t_bres *data);
/*
** Options for fdf
** ============================================================================
*/
void						options_fdf(t_data **mi, t_mlx **mlx);
/*
** Scroll
*/
int							change_height(int key, int x, int y, t_data **mi);
/*
** Arrows map movement and zooms
*/
int							deal_key(int key, t_data **mi);
/*
** Black and white
*/
void						black_and_white(t_data **mi);
void						change_img_add(t_data **mai);
/*
** Rotations and Perspective change
*/
void						change_perspective(t_data **mi);
void						choosing_projection(t_data **mai, int projection);
/*
** ============================================================================
*/
#endif
