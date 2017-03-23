#include "../includes/wolf3d.h"
#include "../frameworks/SDL2.framework/Headers/SDL.h"

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
			if (world->map[i / 100][j / 100] == 1)
				pixel_to_image(screen, j, i, RED);
			else
				pixel_to_image(screen, j, i, BLACK);				
			j++;
		}
		i++;
	}
}

int     edit_map(t_world *world, SDL_Window *window, SDL_Surface *screen, SDL_Event event)
{
		if (event.key.keysym.sym == SDLK_e)
    	return (1);
		if (event.button.button == SDL_BUTTON_LEFT)
			world->map[event.button.y / 100][event.button.x / 100] = 1; 
		if (event.button.button == SDL_BUTTON_RIGHT)
			world->map[event.button.y / 100][event.button.x / 100] = 0; 
		draw_map(world, screen);
	return (0);
}

void    map_editor(t_world *world)
{
    SDL_Window		*window;
	SDL_Surface 	*screen;
	SDL_Event		event;
    int				quit;
    
    window = NULL;
    quit = 0;
//Initialize SDL	
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
//Set up window
	window = SDL_CreateWindow("Wolf 3D v1.0 Beta", 100, 100, EDITOR_WIN_WIDTH, EDITOR_WIN_HEIGHT, 0);
	screen = SDL_GetWindowSurface(window);

	while(quit == 0)
    {
		while(SDL_PollEvent(&event))
			quit = edit_map(world, window, screen, event);
		SDL_UpdateWindowSurface(window);
	}
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
}