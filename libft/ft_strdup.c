/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 13:52:57 by gvirga            #+#    #+#             */
/*   Updated: 2018/10/25 03:31:46 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		size;
	char		*copy;

	size = ft_strlen(s1);
	copy = ft_strnew(size);
	if (copy)
	{
		while (size--)
			copy[size] = s1[size];
	}
	return (copy);
}
