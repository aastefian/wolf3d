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
#include "../libft/libft.h"
#include "../frameworks/SDL2.framework/Headers/SDL.h"
#include <fcntl.h>

void	pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8 *pixel;

	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

/*
* Initialize SDL and start listening to events
* On event receive send data to handler
*/

void	wolf3d(t_world *world)
{
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_Event		event;
	int				quit;
	t_mask			mask;

	quit = 0;
	window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
	window = SDL_CreateWindow("Wolf 3D v1.0 Beta", 100, 100, WIN_WIDTH,
								WIN_HEIGHT, 0);
	screen = SDL_GetWindowSurface(window);
	world->window.image = screen;
	render(world);
	while (quit == 0)
	{
		while (SDL_PollEvent(&event))
			quit = wolf3d_handler(world, screen, event);
		SDL_UpdateWindowSurface(window);
	}
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
}

/*
* 	FILE *saved = stdout;
*	stdout = fopen("log.txt", "w+");
*/

int		main(int argc, char **argv)
{
	int		**map;
	t_world	*world;
	int		fd;

	map = NULL;
	if (argc == 2)
	{
		if (!(world = (t_world*)malloc(sizeof(t_world) * 1)))
		{
			ft_putstr("Not enough memory\n");
			exit(0);
		}
		load_map(&map, argv[1]);
		world->player.x = 600;
		world->player.y = 600;
		world->player.orientation = 0;
		world->player.speed = 10;
		world->map = map;
		wolf3d(world);
	}
	else
		ft_putstr("Usage: ./wolf3d [map_name]\n");
	SDL_Quit();
	return (0);
}
