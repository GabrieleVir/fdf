/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_freei.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:42:17 by gvirga            #+#    #+#             */
/*   Updated: 2018/12/10 18:16:10 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_freei(char const *s1, char const *s2, int n, int pos)
{
	int		i;
	int		u;
	char	*conc_str;

	if (!s1 || !s2 || n < 0 || n > 3)
		return (NULL);
	i = -1;
	if ((conc_str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		while (++i < pos)
			conc_str[i] = s1[i];
		u = -1;
		while (s2[++u])
			conc_str[i++] = s2[u];
		if (n == 2 || n == 3)
			free((char *)s2);
		i = i - u;
		while (s1[i])
			conc_str[pos + u++] = s1[i++];
		if (n == 1 || n == 3)
			free((char *)s1);
		conc_str[u + pos] = '\0';
	}
	return (conc_str);
}
