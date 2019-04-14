/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 21:02:05 by gvirga            #+#    #+#             */
/*   Updated: 2018/12/11 21:18:12 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*error(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

char			*ft_strsub_free(char const *s, unsigned int start, size_t len)
{
	char	*slice;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((slice = ft_strnew(len)))
	{
		while (i < len)
		{
			slice[i] = (char)s[start];
			start++;
			i++;
		}
		slice[i] = '\0';
		free((char*)s);
		s = NULL;
		return (slice);
	}
	else
		return (error((char*)s));
}
