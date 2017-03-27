/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 11:05:44 by svilau            #+#    #+#             */
/*   Updated: 2016/10/21 14:50:58 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include <stdlib.h>

void	alloc_map(int ***map, int map_width, int map_height)
{
	int i;

	i = 0;
	if (!(*map = (int **)malloc(sizeof(int *) * map_height)))
		return ;
	while (i < map_height)
	{
		if (!((*map)[i] = (int *)malloc(sizeof(int) * map_width)))
			return ;
		i++;
	}
}

void	load_map(int ***map, char *map_name)
{
	int i;
	int j;

	(void)map_name;
	alloc_map(map, MAP_WIDTH, MAP_HEIGHT);
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (i == 0 || j == 0 || i == MAP_HEIGHT - 1 || j == MAP_WIDTH - 1)
				(*map)[i][j] = 1;
			else
				(*map)[i][j] = 0;
			j++;
		}
		i++;
	}
}
