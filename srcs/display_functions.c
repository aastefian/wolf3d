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
#include "../frameworks/SDL2.framework/Headers/SDL.h"

void	pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8 *pixel;

	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

void	print_line(t_world *world, int length, int x, int color)
{
	int y;

	y = 0;
	while (y < WIN_HEIGHT - (WIN_HEIGHT - length) / 2)
	{
		if (y < (WIN_HEIGHT - length) / 2)
		{
			pixel_to_image(world->window.image, x, y, SKY_COLOR);
			y++;
			continue;
		}
		pixel_to_image(world->window.image, x, y, color);
		if (x <= (WIN_WIDTH) / 2 + 1 && x >= WIN_WIDTH / 2 - 1 && y <=
				WIN_HEIGHT / 2 + 1 && y >= WIN_HEIGHT / 2 - 1)
			pixel_to_image(world->window.image, x, y, DARK_PINK);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		pixel_to_image(world->window.image, x, y, GROUND_COLOR);
		y++;
	}
}
