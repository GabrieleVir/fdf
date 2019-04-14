/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_npower.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 00:24:15 by gvirga            #+#    #+#             */
/*   Updated: 2018/12/04 00:28:36 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_npower(double c, int power)
{
	double		result;

	result = 1;
	if (power == 0 || c == 1)
		return (1);
	if (power > 0 || c < 0)
		return (-1);
	if (c == 0)
		return (0);
	while (power++)
		result /= c;
	return (result);
}
