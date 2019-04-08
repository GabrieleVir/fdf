/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 20:39:45 by gvirga            #+#    #+#             */
/*   Updated: 2018/12/11 20:41:19 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew_free(size_t size, char *str)
{
	char	*mal_str;

	free(str);
	if (str)
		str = NULL;
	mal_str = (char *)ft_memalloc(sizeof(*mal_str) * (size + 1));
	if (!mal_str)
		return (NULL);
	return (mal_str);
}
