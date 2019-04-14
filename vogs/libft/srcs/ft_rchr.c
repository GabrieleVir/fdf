/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:01:46 by gvirga            #+#    #+#             */
/*   Updated: 2018/12/10 11:54:33 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_rchr(char *str, char c)
{
	int		i;
	char	*tmp;
	int		u;

	if (!str || !c)
		return (NULL);
	i = ft_strchri(str, c);
	u = -1;
	if (i != 0)
	{
		if (!(tmp = ft_strnew(ft_strlen(str) - 1)))
			return (NULL);
		while (++u < i - 1)
			tmp[u] = str[u];
		while (++u < (int)ft_strlen(str))
			tmp[u] = str[u];
		tmp[u] = '\0';
		free(str);
		str = tmp;
		return (str);
	}
	else
		return (NULL);
}
