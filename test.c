/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvirga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 06:30:57 by gvirga            #+#    #+#             */
/*   Updated: 2019/03/20 06:32:39 by gvirga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int			main(int ac, char **av)
{
	int		x = atoi(av[1]);
	printf("%d\n", x / 2);
	printf("%d\n", x >> 1);
	return (0);
}
