/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 21:06:03 by gvirga            #+#    #+#             */
/*   Updated: 2019/01/03 11:37:55 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_digit_base(intmax_t nbr, int base)
{
	int		nbr_digit;

	if (base <= 1)
		return (-1);
	nbr_digit = 1;
	while (nbr >= base)
	{
		nbr /= base;
		nbr_digit++;
	}
	return (nbr_digit);
}

static int		intmax_min(intmax_t nbr)
{
	if (nbr == INTMAX_MIN)
		return (1);
	return (0);
}

static char		*strnbr_conversion(intmax_t nbr, int base, int sign)
{
	int		nb_digit;
	int		modulo;
	int		i;
	char	*strnbr;

	i = -1;
	nb_digit = nb_digit_base(nbr, base);
	if (!(strnbr = (char*)malloc(sizeof(char) * nb_digit + sign + 1)))
		return (NULL);
	if (sign)
		strnbr[0] = '-';
	while (++i < nb_digit)
	{
		modulo = nbr % base;
		if (modulo > 9)
			strnbr[nb_digit + sign - 1 - i] = 'a' + modulo - 10;
		else
			strnbr[nb_digit + sign - 1 - i] = modulo + '0';
		nbr /= base;
	}
	strnbr[nb_digit + sign] = '\0';
	return (strnbr);
}

char			*ft_itoa_base(intmax_t nbr, int base)
{
	int				i;
	int				sign;
	char			*strnbr;
	intmax_t		result;

	if (base <= 1 || base > 16)
		return (NULL);
	result = nbr;
	i = -1;
	sign = 0;
	if (nbr < 0)
	{
		sign = 1;
		if (intmax_min(nbr))
			result = INTMAX_MAX;
		else
			result = -nbr;
	}
	if (!(strnbr = strnbr_conversion(result, base, sign)))
		return (NULL);
	if (intmax_min(nbr))
		strnbr[19] += 1;
	return (strnbr);
}
