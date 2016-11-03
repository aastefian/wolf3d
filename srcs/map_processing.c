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

void	load_map(int ***map, char *map_name)
{
	int i;

	int mapWitdh = MAP_WIDTH;
	int mapHeight = MAP_HEIGHT;

	i = 0;
	(void)map_name;
	if (!(*map = (int **)malloc(sizeof(int *) * 5)))
		return;
	while (i < 5)
	{
		if (!((*map)[i] = (int *)malloc(sizeof(int) * 5)))
			return;
		i++;
	}

	int local_map[5][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 1, 1},
	    {1, 0, 0, 1, 1},
	    {1, 0, 0, 1, 1},
	    {1, 1, 1, 1, 1},
	};

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapHeight; j++)
			(*map)[i][j] = local_map[i][j];
	}
}