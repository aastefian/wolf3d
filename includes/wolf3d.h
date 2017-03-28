/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:50:12 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:08:54 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <SDL2/SDL.h>
# include <math.h>

# define PI 3.141592
# define WIN_WIDTH 960
# define WIN_HEIGHT 540

# define MAP_WIDTH 11
# define MAP_HEIGHT 11

# define EDITOR_WIN_WIDTH 1100
# define EDITOR_WIN_HEIGHT 1100

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
# define DARK_PINK 16711935
# define SKY_BLUE 8900331
# define LIGHT_BROWN 12624511

# define NORTH_COLOR RED
# define EAST_COLOR GREEN
# define WEST_COLOR ORANGE
# define SOUTH_COLOR BLUE

# define PLAYER_COLOR BLUE
# define STANDARD_WALL_COLOR LIGHT_BROWN
# define EMPTY_SPACE_COLOR BLACK

# define SKY_COLOR SKY_BLUE
# define GROUND_COLOR LIGHT_BROWN

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
	double	x;
	double	y;
	char	axis;
	int		color;
	t_tile	tile;
	double	distance;
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
	SDL_Window		*win;
}					t_window;

typedef struct		s_keys
{
	int shift;
	int up;
}					t_keys;

typedef struct		s_world
{
	t_player	player;
	int			**map;
	t_window	window;
	t_keys		*keys;
}					t_world;

void				pixel_to_image(SDL_Surface *surface, int x, int y,
						Uint32 color);

int					wolf3d_event_handler(t_world *world, SDL_Surface *screen,
						SDL_Event event);

void				load_map(t_world *world, int ***map, char *map_name);

void				render(t_world *world);

void				map_editor(t_world *world);

void				print_line(t_world *world, int length, int x, int color);

double				get_next_ray_angle(double player_orientation, int index);

void				cast_ray(t_collision *collision, t_world *world,
						double angle);

void				get_first_intersection_vertical(t_collision *collision_v,
						int player_x, int player_y, double angle);

void				get_first_intersection_horizontal(t_collision *collision_h,
						int player_x, int player_y, double angle);

void				get_next_intersection_vertical(t_collision *collision_v,
						double angle);

void				get_next_intersection_horizontal(t_collision *collision_h,
						double angle);

int					check_collision_vertical(t_world *world,
						t_collision *collision_v, double angle);

int					check_collision_horizontal(t_world *world,
						t_collision *collision_h, double angle);

int					player_collide_forward(t_world world);

int					player_collide_backward(t_world world);

void				move_player_forward(int *player_x, int *player_y,
						double player_orientation, int player_speed);

void				move_player_backward(int *player_x, int *player_y,
						double player_orientation, int player_speed);

void				free_map(t_world *world);

void				free_world(t_world *world);

void				free_up_to_i(int ***map, int i);

#endif
