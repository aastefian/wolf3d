/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:09:12 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <math.h>
#include "../frameworks/SDL2.framework/Headers/SDL.h"

t_tile	get_point_tile(int x, int y)
{
	t_tile point_tile;

	point_tile.x = floor(x / CUBE_SIZE);
	point_tile.y = floor(y / CUBE_SIZE);
	return (point_tile);
}

double	get_distance_cos(int x1, int x2, double angle)
{
	return (abs(x1 - x2) / cos(angle));
}

double	get_distance_sin(int x1, int x2, double angle)
{
	return (abs(x1 - x2) / sin(angle));
}

int		check_collision_vertical(t_world *world, t_collision *collision_v,
									double angle)
{
	t_tile first_tile;

	first_tile = get_point_tile(collision_v->x, collision_v->y);
	if (first_tile.x >= 0 && first_tile.x < MAP_WIDTH && first_tile.y >= 0 &&
		first_tile.y < MAP_HEIGHT && world->map[first_tile.y][first_tile.x])
	{
		if (0 < angle && angle < RADIANS_90)
			collision_v->distance = get_distance_cos(world->player.x,
									collision_v->x, fmod(angle, RADIANS_90));
		else if (RADIANS_90 < angle && angle < RADIANS_180)
			collision_v->distance = get_distance_sin(world->player.x,
									collision_v->x, fmod(angle, RADIANS_90));
		else if (RADIANS_180 < angle && angle < RADIANS_270)
			collision_v->distance = get_distance_cos(world->player.x,
									collision_v->x, fmod(angle, RADIANS_90));
		else if (RADIANS_270 < angle && angle < RADIANS_360)
			collision_v->distance = get_distance_sin(world->player.x,
									collision_v->x, fmod(angle, RADIANS_90));
		collision_v->tile.x = first_tile.x;
		collision_v->tile.y = first_tile.y;
		return (1);
	}
	return (0);
}

int		check_collision_horizontal(t_world *world, t_collision *collision_h,
									double angle)
{
	t_tile first_tile;

	first_tile = get_point_tile(collision_h->x, collision_h->y);
	if (first_tile.x >= 0 && first_tile.x < MAP_WIDTH && first_tile.y >= 0 &&
		first_tile.y < MAP_HEIGHT && world->map[first_tile.y][first_tile.x])
	{
		if (0 < angle && angle < RADIANS_90)
			collision_h->distance = get_distance_sin(world->player.y,
									collision_h->y, fmod(angle, RADIANS_90));
		else if (RADIANS_90 < angle && angle < RADIANS_180)
			collision_h->distance = get_distance_cos(world->player.y,
									collision_h->y, fmod(angle, RADIANS_90));
		else if (RADIANS_180 < angle && angle < RADIANS_270)
			collision_h->distance = get_distance_sin(world->player.y,
									collision_h->y, fmod(angle, RADIANS_90));
		else if (RADIANS_270 < angle && angle < RADIANS_360)
			collision_h->distance = get_distance_cos(world->player.y,
									collision_h->y, fmod(angle, RADIANS_90));
		collision_h->tile.x = first_tile.x;
		collision_h->tile.y = first_tile.y;
		return (1);
	}
	return (0);
}
