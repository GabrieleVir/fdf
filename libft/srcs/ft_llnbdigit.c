/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llnbdigit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:19:16 by gvirga            #+#    #+#             */
/*   Updated: 2019/02/08 16:48:58 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_llnbdigit(long long nbr)
{
	int		i;

	i = 1;
	if (nbr == LLONG_MIN || nbr == LLONG_MAX)
		return (18);
	if (nbr == 0)
		return (1);
	if (nbr > 0)
	{
		while (nbr > 10)
		{
			i++;
			nbr /= 10;
		}
	}
	else
		ft_llnbdigit(-nbr);
	return (i);
}
