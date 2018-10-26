/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:33:26 by gvirga            #+#    #+#             */
/*   Updated: 2018/10/26 20:33:34 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount2(char *str, char c, char c1)
{
	size_t		i;
	size_t		k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i] != c1)
		{
			k++;
			while (str[i] != c && str[i] != '\0' && str[i] != c1)
				i++;
		}
		else
			i++;
	}
	return (k);
}
