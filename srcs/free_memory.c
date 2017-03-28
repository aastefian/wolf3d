/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
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

void		free_up_to_i(int ***map, int i)
{
	while (i >= 0)
	{
		free((*map)[i]);
		i--;
	}
	free(*map);
}

void		free_map(t_world *world)
{
	int i;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		free(world->map[i]);
		i++;
	}
	free(world->map);
}

void		free_world(t_world *world)
{
	free(world);
}
