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

void	move_player_forward(int *player_x, int *player_y,
								double player_orientation, int player_speed)
{
	if (0 < player_orientation && player_orientation < RADIANS_90)
	{
		*player_y -= sin(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x += cos(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_90 < player_orientation && player_orientation < RADIANS_180)
	{
		*player_y -= cos(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x -= sin(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_180 < player_orientation && player_orientation < RADIANS_270)
	{
		*player_y += sin(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x -= cos(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_270 < player_orientation && player_orientation < RADIANS_360)
	{
		*player_y += cos(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x += sin(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
}

void	move_player_backward(int *player_x, int *player_y,
			double player_orientation, int player_speed)
{
	if (0 < player_orientation && player_orientation < RADIANS_90)
	{
		*player_y += sin(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x -= cos(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_90 < player_orientation && player_orientation < RADIANS_180)
	{
		*player_y += cos(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x += sin(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_180 < player_orientation && player_orientation < RADIANS_270)
	{
		*player_y -= sin(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x += cos(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_270 < player_orientation && player_orientation < RADIANS_360)
	{
		*player_y -= cos(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x -= sin(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
}
