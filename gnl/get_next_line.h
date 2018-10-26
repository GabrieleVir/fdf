/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:21:00 by gvirga            #+#    #+#             */
/*   Updated: 2018/10/01 15:36:31 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 128

# include <sys/types.h>
# include <sys/uio.h>
# include <limits.h>
# ifndef OPEN_MAX
#  define OPEN_MAX 1000
# endif
# include "libft.h"

int		get_next_line(const int fd, char **line);

#endif