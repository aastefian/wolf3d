/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_backward.c                        :+:      :+:    :+:   */
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

int		player_collide_backward_2(t_world world)
{
	if (RADIANS_180 < world.player.orientation && world.player.orientation <
	RADIANS_270 &&
	world.map[(int)((world.player.y - (sin(fmod(world.player.orientation,
	RADIANS_90)) * world.player.speed)) / CUBE_SIZE)][(int)((world.player.x +
	(cos(fmod(world.player.orientation, RADIANS_90)) * world.player.speed)) /
	CUBE_SIZE)] == 0)
		return (0);
	if (RADIANS_270 < world.player.orientation && world.player.orientation <
	RADIANS_360 &&
	world.map[(int)((world.player.y - (cos(fmod(world.player.orientation,
	RADIANS_90)) * world.player.speed)) / CUBE_SIZE)][(int)((world.player.x -
	(sin(fmod(world.player.orientation, RADIANS_90)) * world.player.speed)) /
	CUBE_SIZE)] == 0)
		return (0);
	return (1);
}

int		player_collide_backward(t_world world)
{
	if (0 < world.player.orientation && world.player.orientation <
	RADIANS_90 &&
	world.map[(int)((world.player.y + (sin(fmod(world.player.orientation,
	RADIANS_90)) * world.player.speed)) / CUBE_SIZE)][(int)((world.player.x -
	(cos(fmod(world.player.orientation, RADIANS_90)) * world.player.speed)) /
	CUBE_SIZE)] == 0)
		return (0);
	if (RADIANS_90 < world.player.orientation && world.player.orientation <
	RADIANS_180 &&
	world.map[(int)((world.player.y + (cos(fmod(world.player.orientation,
	RADIANS_90)) * world.player.speed)) / CUBE_SIZE)][(int)((world.player.x +
	(sin(fmod(world.player.orientation, RADIANS_90)) * world.player.speed)) /
	CUBE_SIZE)] == 0)
		return (0);
	if (player_collide_backward_2(world) == 0)
		return (0);
	return (1);
}
