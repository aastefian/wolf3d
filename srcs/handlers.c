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

void	key_press_handler1(t_world *world, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LSHIFT)
	{
		if (world->player.speed == 10)
			world->player.speed *= 10;
		else
			world->player.speed = 10;
	}
	if (event.key.keysym.sym == SDLK_UP)
		if (player_collide_forward(*world) == 0)
			move_player_forward(&(world->player.x), &(world->player.y),
							world->player.orientation, world->player.speed);
	if (event.key.keysym.sym == SDLK_DOWN)
		if (player_collide_backward(*world) == 0)
			move_player_backward(&(world->player.x), &(world->player.y),
							world->player.orientation, world->player.speed);
}

void	key_press_handler2(t_world *world, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LEFT)
		world->player.orientation = fmod((world->player.orientation +
											0.01), PI * 2);
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		world->player.orientation = fmod((world->player.orientation -
											0.01), PI * 2);
		if (world->player.orientation < 0)
			world->player.orientation += PI * 2;
	}
	if (event.key.keysym.sym == SDLK_e)
		map_editor(world);
}

void	mouse_movement(t_world *world)
{
	int	mouse_x;

	SDL_GetRelativeMouseState(&mouse_x, NULL);
	if (mouse_x < 0)
	{
		world->player.orientation = fmod((world->player.orientation +
										0.05), PI * 2);
	}
	else if (mouse_x > 0)
	{
		world->player.orientation = fmod((world->player.orientation -
										0.05), PI * 2);
		if (world->player.orientation < 0)
			world->player.orientation += PI * 2;
	}
	mouse_x = 0;
}

int		wolf3d_event_handler(t_world *world, SDL_Surface *screen,
										SDL_Event event)
{
	static int mouse_x;

	if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == SDLK_ESCAPE))
		return (1);
	SDL_SetRelativeMouseMode(1);
	mouse_movement(world);
	if (event.type == SDL_KEYDOWN)
	{
		key_press_handler1(world, event);
		key_press_handler2(world, event);
	}
	return (0);
}
