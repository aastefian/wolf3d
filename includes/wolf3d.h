/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:50:12 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:08:54 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_3D_H
# include <SDL2/SDL.h>
# include <math.h>

# define _WOLF_3D_H
# define PI 3.141592
// # define WIN_WIDTH (int) (960 / 100)
// # define WIN_HEIGHT (int) (540 / 100)
# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define EDITOR_WIN_WIDTH 1100
# define EDITOR_WIN_HEIGHT 1100
# define WIN_BPP 32
# define MAP_WIDTH 11
# define MAP_HEIGHT 11
# define VIEW_DISTANCE 10
# define FOV_RADIANS 1.0471975512
# define RADIANS_30 0.5235987756
# define RADIANS_45 0.7853981634
# define RADIANS_60 1.0471975512
# define RADIANS_90 1.5707963268
# define RADIANS_180 3.1415926536
# define RADIANS_270 4.7123889804
# define RADIANS_359 6.2657320147 
# define RADIANS_360 6.2831853072
# define CUBE_SIZE 512
# define BLACK 0
# define WHITE 16777215
# define RED 16737380
# define BLUE 49151
# define GREEN 8190976
# define ORANGE 16753920
# define NORTH_COLOR RED
# define EAST_COLOR GREEN
# define WEST_COLOR ORANGE
# define SOUTH_COLOR BLUE
# define STANDARD_WALL_COLOR RED
# define EMPTY_SPACE_COLOR BLACK
# define BOUND_RIGHT 190

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
	int x;
	int y;
	int color;
	t_tile	tile;
	double 	distance;
}					t_collision;

typedef struct		s_player
{
	int		x;
	int		y;
	int		speed;
	double	orientation;
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
int		wolf3d_handler(t_world *world, SDL_Surface *screen, SDL_Event event);
void	load_map(int ***map, char *map_name);
void	render(t_world *world);
void    map_editor(t_world *world);
void	print_line(t_world *world, int length, int x, int color);

#endif
