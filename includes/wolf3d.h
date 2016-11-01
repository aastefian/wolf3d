/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:50:12 by svilau            #+#    #+#             */
/*   Updated: 2016/10/21 11:56:22 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_3D_H
# include <SDL2/SDL.h>
# define _WOLF_3D_H
# define WIN_WIDTH 320
# define WIN_HEIGHT 200
# define WIN_BPP 32
# define MAP_WIDTH 5
# define MAP_HEIGHT 5
# define FOV_RADIANS 1.0472
# define RADIANS_30 0.523599
# define RADIANS_45 0.785398
# define RADIANS_60 1.0472
# define RADIANS_90 1.5708
# define RADIANS_180 3.14159
# define RADIANS_270 4.71239
# define RADIANS_359 6.26573
#define CUBE_SIZE 64

typedef struct		s_2d_p
{
	int x;
	int y;
	int color;
}					t_2d_p;

typedef struct		s_mask
{
	unsigned int rmask;
	unsigned int gmask;
	unsigned int bmask;
	unsigned int amask;
}					t_mask;

typedef struct		s_tile
{
	int x;
	int y;
}					t_tile;

typedef struct		s_collision
{
	t_tile	tile;
	float 	distance;
}					t_collision;

typedef struct		s_player
{
	int		x;
	int		y;
	float	orientation;
}					t_player;

typedef struct		s_window
{
	SDL_Surface		*image;
}					t_window;

typedef struct		s_world
{
	t_player	player;
	int 		**map;
	t_window	window;
}					t_world;

void	pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color);
int	wolf3d_handler(t_world *world, SDL_Surface *screen, SDL_Event event);
void	load_map(int ***map, char *map_name);

#endif
