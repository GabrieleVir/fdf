/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 04:33:03 by gvirga            #+#    #+#             */
/*   Updated: 2018/12/12 04:33:33 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(const char *s1, char *str)
{
	size_t		size;
	char		*copy;

	size = ft_strlen(s1) + 1;
	copy = (char*)malloc(sizeof(*copy) * size);
	if (copy)
		ft_memcpy(copy, s1, size);
	free(str);
	str = NULL;
	return (copy);
}
