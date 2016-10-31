/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2016/10/27 16:39:54 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

float	deg_tan(float deg_angle)
{
	return ((float)(tan(deg_angle * (M_PI) / 180)));
}

t_collision	*cast_ray(t_world *world, float angle)
{
	t_2d_p inters_v;
	t_2d_p inters_h;
}

void	render(t_world *world)
{
	int			i;
	float		angle;
	t_collision	*collision;

	i = 0;
	angle = world->player.orientation + RADIANS_30;
	//printf("%f\n", angle);
	while (i < WIN_WIDTH)
	{
	 	//collision = cast_ray(world, angle);
		//get_distance(world->player.x, world->player.y, colision.x, collision.y);
	 	angle += ((int)FOV / (float)WIN_WIDTH);
	 	i++;
	 }
}

void	wolf3d_handler(t_world *world, SDL_Surface *screen, SDL_Event event)
{
	if (event.type = SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP)
		pixel_to_image(screen, 50, 50, 16777215);
	}
	render(world);
}