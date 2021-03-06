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
#include "../libft/libft.h"

void	alloc_map(t_world *world, int ***map, int map_width, int map_height)
{
	int i;

	i = 0;
	if (!(*map = (int **)malloc(sizeof(int *) * map_height)))
	{
		free_world(world);
		ft_putstr("Not enough memory\n Quiting...\n");
		exit(0);
	}
	while (i < map_height)
	{
		if (!((*map)[i] = (int *)malloc(sizeof(int) * map_width)))
		{
			free_up_to_i(map, i);
			free_world(world);
			ft_putstr("Not enough memory\n Quiting...\n");
			exit(0);
		}
		i++;
	}
}

void	load_map(t_world *world, int ***map, char *map_name)
{
	int i;
	int j;

	(void)map_name;
	alloc_map(world, map, MAP_WIDTH, MAP_HEIGHT);
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
