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

void	data_setup(t_world *world, int **map)
{
	world->player.x = 1000;
	world->player.y = 1000;
	world->player.orientation = 1.58825;
	world->player.speed = 10;
	world->map = map;
}

/*
**	Set the game in fullscreen
**	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
*/

/*
**	Initialize SDL and start listening to events
**	On event receive send data to handler
*/

void	wolf3d(t_world *world)
{
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_Event		event;
	int				quit;

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
		SDL_PollEvent(&event);
		quit = wolf3d_event_handler(world, screen, event);
		render(world);
		SDL_UpdateWindowSurface(window);
	}
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
}

/*
**	int fd;
**	FILE *saved = stdout;
**	stdout = fopen("log.txt", "w+");
*/

int		main(int argc, char **argv)
{
	int		**map;
	t_world	*world;

	map = NULL;
	if (argc == 1)
	{
		if (!(world = (t_world*)malloc(sizeof(t_world) * 1)))
		{
			ft_putstr("Not enough memory\n");
			exit(0);
		}
		load_map(world, &map, argv[1]);
		data_setup(world, map);
		wolf3d(world);
		free_map(world);
		free_world(world);
	}
	else
		ft_putstr("Usage: ./wolf3d\n");
	SDL_Quit();
	return (0);
}

/*
**	When saved maps are coded, show this usage message
**	ft_putstr("Usage: ./wolf3d [map_name]\n");
*/
