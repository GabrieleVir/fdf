/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_rounding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 04:50:36 by gvirga            #+#    #+#             */
/*   Updated: 2019/02/14 07:19:29 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nine_loop(char **str, size_t *len)
{
	while ((*str)[(*len)] == '9')
	{
		(*str)[(*len)] = '0';
		(*len)--;
		if ((*str)[(*len)] == '.')
			(*len)--;
		if ((*len) == 0 && (*str)[(*len)] == '9')
		{
			(*str)[(*len)] = '0';
			return (2);
		}
	}
	return (1);
}

static int	ceiling(char **str, size_t len)
{
	int		ceil_digit;

	if ((*str)[len] == '.')
		len--;
	if ((*str)[len] > '5')
	{
		if ((*str)[len] == '9')
		{
			ceil_digit = nine_loop(str, &len);
			if (ceil_digit == 2)
				return (2);
			(*str)[len] += 1;
		}
		else
		{
			len--;
			if ((*str)[len] == '.')
				len--;
			(*str)[len] += 1;
		}
		return (0);
	}
	return (0);
}

char		*round_str_double(char *str)
{
	size_t	len;
	size_t	tmp;
	int		ceiling_in_process;
	char	*rounded_str;

	len = ft_strlen(str);
	rounded_str = ft_strdup(str);
	tmp = len;
	len--;
	while ((ceiling_in_process = ceiling(&rounded_str, len)))
		len--;
	if (ceiling_in_process == 2)
		rounded_str = ft_strjoin_free("1", rounded_str, 2);
	rounded_str = ft_strsub_free(rounded_str, 0, tmp - 1);
	return (rounded_str);
}
