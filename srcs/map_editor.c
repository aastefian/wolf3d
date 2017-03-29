/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include "../frameworks/SDL2.framework/Headers/SDL.h"

void	handle_mouse_motion(t_world *world, SDL_Event event)
{
	if (event.motion.state == SDL_BUTTON(SDL_BUTTON_RIGHT))
		world->map[event.button.y / BLOCK_SIZE][event.button.x /
					BLOCK_SIZE] = 0;
	if (event.motion.state == SDL_BUTTON(SDL_BUTTON_LEFT) &&
			(world->player.y / CUBE_SIZE != event.button.y / BLOCK_SIZE ||
			world->player.x / CUBE_SIZE != event.button.x / BLOCK_SIZE))
		world->map[event.button.y / BLOCK_SIZE][event.button.x /
					BLOCK_SIZE] = 1;
}

void	draw_map(t_world *world, SDL_Surface *screen)
{
	int i;
	int j;

	i = 0;
	while (i < EDITOR_WIN_HEIGHT)
	{
		j = 0;
		while (j < EDITOR_WIN_WIDTH)
		{
			if (world->map[i / BLOCK_SIZE][j / BLOCK_SIZE] == 1)
				pixel_to_image(screen, j, i, STANDARD_WALL_COLOR);
			else if (world->player.y / CUBE_SIZE == i / BLOCK_SIZE &&
			world->player.x /
				CUBE_SIZE == j / BLOCK_SIZE)
				pixel_to_image(screen, j, i, PLAYER_COLOR);
			else
				pixel_to_image(screen, j, i, EMPTY_SPACE_COLOR);
			j++;
		}
		i++;
	}
}

int		edit_map(t_world *world, SDL_Window *window, SDL_Surface *screen,
					SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
		return (1);
	if (event.type == SDL_MOUSEMOTION)
		handle_mouse_motion(world, event);
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_RIGHT)
			world->map[event.button.y / BLOCK_SIZE][event.button.x /
						BLOCK_SIZE] = 0;
		if (event.button.button == SDL_BUTTON_LEFT &&
			(world->player.y / CUBE_SIZE != event.button.y / BLOCK_SIZE ||
				world->player.x / CUBE_SIZE != event.button.x / BLOCK_SIZE))
			world->map[event.button.y / BLOCK_SIZE][event.button.x /
						BLOCK_SIZE] = 1;
	}
	draw_map(world, screen);
	return (0);
}

void	map_editor(t_world *world)
{
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_Event		event;
	int				quit;

	window = NULL;
	quit = 0;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
	SDL_SetRelativeMouseMode(0);
	window = SDL_CreateWindow("Wolf 3D Map Editor", BLOCK_SIZE, BLOCK_SIZE,
								EDITOR_WIN_WIDTH, EDITOR_WIN_HEIGHT, 0);
	screen = SDL_GetWindowSurface(window);
	while (quit == 0)
	{
		SDL_PollEvent(&event);
		quit = edit_map(world, window, screen, event);
		SDL_UpdateWindowSurface(window);
	}
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
	SDL_SetRelativeMouseMode(1);
}
