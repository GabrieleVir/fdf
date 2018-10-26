/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:32:02 by gvirga            #+#    #+#             */
/*   Updated: 2018/10/26 20:35:09 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(char const *s, char c, char c1)
{
	size_t i;

	i = 0;	
	while (s[i] && s[i] != c && s[i] != c1)
		i++;
	return (i);
}

static char		*next_word(char const *s, char c, char c1)
{
	while (*s && (*s == c || *s == c1))
		s++;
	return ((char *)s);
}

static void		cleanup(char **split, size_t cur)
{
	while (cur > 0)
	{
		cur--;
		ft_strdel(&split[cur]);
	}
	ft_strdel(split);
}

char		**ft_strsplit2(char const *s, char c, char c1)
{
	char	**split;
	size_t	cur;
	size_t	wordcount;

	wordcount = ft_wordcount2((char *)s, c, c1);
	split = (char **)ft_memalloc((wordcount + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	cur = 0;
	while (cur < wordcount)
	{
		s = next_word(s, c, c1);
		split[cur] = ft_strsub(s, 0, word_len(s, c, c1));
		if (split[cur] == NULL)
		{
			cleanup(split, cur);
			return (NULL);
		}
		cur++;
		s += word_len(s, c, c1);
	}
	split[wordcount] = NULL;
	return (split);
}
