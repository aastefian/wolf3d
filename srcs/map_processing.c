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
	int local_map[10][10] = {
		{1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 1, 1},		
		{1, 1, 1, 1, 1, 1},
	};

	(void)map_name;
	alloc_map(map, MAP_WIDTH, MAP_HEIGHT);
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			(*map)[i][j] = local_map[i][j];
			j++;
		}
		i++;
	}
}
