/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection_point.c                           :+:      :+:    :+:   */
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

void	get_first_intersection_vertical(t_collision *collision_v,
			int player_x, int player_y, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		collision_v->x = floor(player_x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collision_v->y = player_y - ((collision_v->x - player_x) *
											tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		collision_v->x = floor(player_x / CUBE_SIZE) * CUBE_SIZE - 1;
		collision_v->y = player_y - ((player_x - collision_v->x) /
											tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		collision_v->x = floor(player_x / CUBE_SIZE) * CUBE_SIZE - 1;
		collision_v->y = player_y + ((player_x - collision_v->x) *
											tan(fmod(angle, RADIANS_90)));
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		collision_v->x = floor(player_x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collision_v->y = player_y + ((collision_v->x - player_x) /
											tan(fmod(angle, RADIANS_90)));
	}
}

void	get_first_intersection_horizontal(t_collision *collision_h,
									int player_x, int player_y, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		collision_h->y = floor(player_y / CUBE_SIZE) * CUBE_SIZE - 1;
		collision_h->x = player_x + ((player_y - collision_h->y) /
											tan(fmod(angle, RADIANS_90)));
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		collision_h->y = floor(player_y / CUBE_SIZE) * CUBE_SIZE - 1;
		collision_h->x = player_x - ((player_y - collision_h->y) *
											tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		collision_h->y = floor(player_y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collision_h->x = player_x - ((collision_h->y - player_y) /
											tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		collision_h->y = floor(player_y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collision_h->x = player_x + ((collision_h->y - player_y) *
											tan(fmod(angle, RADIANS_90)));
	}
}

void	get_next_intersection_vertical(t_collision *collision_v, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		collision_v->x += CUBE_SIZE;
		collision_v->y -= CUBE_SIZE * tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		collision_v->x -= CUBE_SIZE;
		collision_v->y -= CUBE_SIZE / tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		collision_v->x -= CUBE_SIZE;
		collision_v->y += CUBE_SIZE * tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		collision_v->x += CUBE_SIZE;
		collision_v->y += CUBE_SIZE / tan(fmod(angle, RADIANS_90));
	}
}

void	get_next_intersection_horizontal(t_collision *collision_h, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		collision_h->y -= CUBE_SIZE;
		collision_h->x += CUBE_SIZE / tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		collision_h->y -= CUBE_SIZE;
		collision_h->x -= CUBE_SIZE * tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		collision_h->y += CUBE_SIZE;
		collision_h->x -= CUBE_SIZE / tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		collision_h->y += CUBE_SIZE;
		collision_h->x += CUBE_SIZE * tan(fmod(angle, RADIANS_90));
	}
}
