/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 21:58:07 by gvirga            #+#    #+#             */
/*   Updated: 2018/06/23 21:58:37 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount(char *str, char c)
{
	size_t		i;
	size_t		k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			k++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (k);
}
