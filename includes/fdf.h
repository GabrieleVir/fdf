/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 07:09:57 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/17 17:30:16 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
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
	int						*mlx_img;
	int						*img_add;
}							t_mlx;

typedef struct				s_data
{
	int						origin;
	size_t					nb_column;
	size_t					nb_row;
	size_t					nb_of_elems;
	char					*data;
	intmax_t				*z_arr;
	t_mlx					*mlx_data;
}							t_data;

int				starting_with_the_basics();
int				error_msg(int error);
int				read_file(t_data **maps_info, char *file_name);
int				usage_error_msg();
int				length_error_msg();

#endif
