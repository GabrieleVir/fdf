/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_norme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:10:11 by gvirga            #+#    #+#             */
/*   Updated: 2018/11/08 15:10:35 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		main(void)
{
	mlx_data = (t_mlx*)malloc(sizeof(t_mlx));
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, mlx_data.win_width,
			mlx_data.win_height, "42");
	return (0);
}
