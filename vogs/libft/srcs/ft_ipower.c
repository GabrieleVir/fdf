/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ipower.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 00:19:29 by gvirga            #+#    #+#             */
/*   Updated: 2018/12/04 00:27:27 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_ipower(int c, int power)
{
	int		result;

	result = 1;
	if (power == 0 || c == 1)
		return (1);
	if (power < 0 || c < 0)
		return (-1);
	if (c == 0)
		return (0);
	while (power--)
		result *= c;
	return (result);
}
