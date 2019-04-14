/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigpower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 04:38:39 by gvirga            #+#    #+#             */
/*   Updated: 2019/02/14 04:40:14 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uintmax_t	ft_bigpower(int nbr, int exp)
{
	uintmax_t		result;

	if (exp == 0)
		return (1);
	result = (uintmax_t)nbr;
	while (exp-- > 1)
		result *= (uintmax_t)nbr;
	return (result);
}
