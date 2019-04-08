/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:30:00 by gvirga            #+#    #+#             */
/*   Updated: 2019/02/14 07:50:57 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_diff_parts(double nbr, t_nbr_part *part)
{
	int		nbdigit;

	if (nbr <= LLONG_MIN)
		(*part).intp = LLONG_MIN;
	else if (nbr >= LLONG_MAX)
		(*part).intp = LLONG_MAX;
	else
		(*part).intp = (long long)nbr;
	nbdigit = ft_llnbdigit((*part).intp);
	if (nbdigit > 13)
		(*part).dp = 0;
	(*part).dp = nbr - (double)(*part).intp;
}

static void	join_dec_part(char **str, t_nbr_part part, int prec)
{
	long long intp;

	intp = 0;
	if (part.dp < 0)
		part.dp = -part.dp;
	while (prec--)
	{
		part.dp -= (double)intp;
		part.dp *= 10;
		intp = (long long)part.dp;
		*str = ft_strjoin_free(*str, ft_itoa_base(intp, 10), 3);
	}
	part.dp -= (double)intp;
	part.dp *= 10;
	intp = (long long)part.dp;
	if (*str)
		*str = ft_strjoin_free(*str, ft_itoa_base(intp, 10), 3);
}

char		*ft_ftoa(long double nbr, int prec)
{
	t_nbr_part			nbr_part;
	char				*str;

	str = NULL;
	if (prec == -1)
		prec = 6;
	if (prec > 49)
		prec = 49;
	fill_diff_parts(nbr, &nbr_part);
	str = ft_itoa_base(nbr_part.intp, 10);
	if (prec != 0)
		str = ft_strjoin_free(str, ".", 1);
	if (str)
	{
		join_dec_part(&str, nbr_part, prec);
		if (str)
			str = round_str_double(str);
	}
	return (str);
}
