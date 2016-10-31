/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2016/10/21 16:31:54 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include "../libft/libft.h"
#include <SDL2/SDL.h>

void pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint32));
    *((Uint32*)pixel) = color;
}

void	wolf3d(t_world *world)
{
	SDL_Window		*window;
	SDL_Surface 	*screen;
	SDL_Event		event;
	int				quit;
	t_mask			mask;

	quit = 0;
	window = NULL;
//Initialize SDL	
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
//Set up window
	window = SDL_CreateWindow("Wolf 3D v1.0 Beta", 100, 100, WIN_WIDTH, WIN_HEIGHT, 0);
	screen = SDL_GetWindowSurface(window);
	pixel_to_image(screen, 100, 100, 16777215);
	while(quit == 0)
    {

		while(SDL_PollEvent(&event))
        {
			wolf3d_handler(world, screen, event);
			if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
            {
                //Quit the program
                quit = 1;
            }
		}
		SDL_UpdateWindowSurface(window);
  
	}
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
    //Initialize imag, and image buffer
	//wolf3d_handler(map, mini_l, img);
}

int	main(int argc, char **argv)
{
	int 	**map;
	t_world	*world;

	map = NULL;
	if (argc == 2)
	{
		if (!(world = (t_world*)malloc(sizeof(t_world) * 1)))
		{
			ft_putstr("Not enough memory\n");
			exit(0);
		}
		load_map(&map, argv[1]);
		world->player.x = 160;
		world->player.y = 160;
		world->player.orientation = RADIANS_60;
		world->map = map;
		wolf3d(world);
	}
	else
	{
		ft_putstr("Usage: ./wolf3d [map_name]\n");
	}
	SDL_Quit();
	return (0);
}