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

void	print_line(t_world *world, int length, int x, int color)
{
	int y;

	y = 0;
	while (y < WIN_HEIGHT - (WIN_HEIGHT - length) / 2)
	{
		if (y < (WIN_HEIGHT - length) / 2)
		{
			y++;
			continue;
		}
		pixel_to_image(world->window.image, x, y, color);
		y++;
	}
}

void	collision_initialize(t_collision *collision)
{
	collision->distance = 0;
	collision->tile.x = 0;
	collision->tile.y = 0;
}

t_tile	get_point_tile(int x, int y)
{
	t_tile point_tile;

	point_tile.x = floor(x / CUBE_SIZE);
	point_tile.y = floor(y / CUBE_SIZE);
	return (point_tile);
}

double	get_distance_cos(int x1, int x2, double angle)
{
	return (abs(x1 - x2) / cos(angle));
}

double	get_distance_sin(int x1, int x2, double angle)
{
	return (abs(x1 - x2) / sin(angle));
}

void	get_first_intersection_vertical(t_world *world, double *collision_x,
			double *collision_y, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		*collision_x = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE +
																	CUBE_SIZE;
		*collision_y = world->player.y - ((*collision_x - world->player.x) *
											tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		*collision_x = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE - 1;
		*collision_y = world->player.y - ((world->player.x - *collision_x) /
											tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		*collision_x = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE - 1;
		*collision_y = world->player.y + ((world->player.x - *collision_x) *
											tan(fmod(angle, RADIANS_90)));
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		*collision_x = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE +
																	CUBE_SIZE;
		*collision_y = world->player.y + ((*collision_x - world->player.x) /
											tan(fmod(angle, RADIANS_90)));
	}
}

void	get_first_intersection_horizontal(t_world *world, double *collision_x,
				double *collision_y, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		*collision_y = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE - 1;
		*collision_x = world->player.x + ((world->player.y - *collision_y) /
											tan(fmod(angle, RADIANS_90)));
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		*collision_y = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE - 1;
		*collision_x = world->player.x - ((world->player.y - *collision_y) *
											tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		*collision_y = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		*collision_x = world->player.x - ((*collision_y - world->player.y) /
											tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		*collision_y = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		*collision_x = world->player.x + ((*collision_y - world->player.y) *
											tan(fmod(angle, RADIANS_90)));
	}
}

int		check_collision_vertical(t_world *world, t_collision *collision_v,
									double angle)
{
	t_tile first_tile;

	first_tile = get_point_tile(collision_v->x, collision_v->y);
	if (first_tile.x >= 0 && first_tile.x < MAP_WIDTH && first_tile.y >= 0 &&
		first_tile.y < MAP_HEIGHT && world->map[first_tile.y][first_tile.x])
	{
		if (0 < angle && angle < RADIANS_90)
			collision_v->distance = get_distance_cos(world->player.x,
									collision_v->x, fmod(angle, RADIANS_90));
		else if (RADIANS_90 < angle && angle < RADIANS_180)
			collision_v->distance = get_distance_sin(world->player.x,
									collision_v->x, fmod(angle, RADIANS_90));
		else if (RADIANS_180 < angle && angle < RADIANS_270)
			collision_v->distance = get_distance_cos(world->player.x,
									collision_v->x, fmod(angle, RADIANS_90));
		else if (RADIANS_270 < angle && angle < RADIANS_360)
			collision_v->distance = get_distance_sin(world->player.x,
									collision_v->x, fmod(angle, RADIANS_90));
		collision_v->tile.x = first_tile.x;
		collision_v->tile.y = first_tile.y;
		return (1);
	}
	return (0);
}

int		check_collision_horizontal(t_world *world, t_collision *collision_h,
									double angle)
{
	t_tile first_tile;

	first_tile = get_point_tile(collision_h->x, collision_h->y);
	if (first_tile.x >= 0 && first_tile.x < MAP_WIDTH && first_tile.y >= 0 &&
		first_tile.y < MAP_HEIGHT && world->map[first_tile.y][first_tile.x])
	{
		if (0 < angle && angle < RADIANS_90)
			collision_h->distance = get_distance_sin(world->player.y,
									collision_h->y, fmod(angle, RADIANS_90));
		else if (RADIANS_90 < angle && angle < RADIANS_180)
			collision_h->distance = get_distance_cos(world->player.y,
									collision_h->y, fmod(angle, RADIANS_90));
		else if (RADIANS_180 < angle && angle < RADIANS_270)
			collision_h->distance = get_distance_sin(world->player.y,
									collision_h->y, fmod(angle, RADIANS_90));
		else if (RADIANS_270 < angle && angle < RADIANS_360)
			collision_h->distance = get_distance_cos(world->player.y,
									collision_h->y, fmod(angle, RADIANS_90));
		collision_h->tile.x = first_tile.x;
		collision_h->tile.y = first_tile.y;
		return (1);
	}
	return (0);
}

void	get_next_intersection_vertical(double *collision_x,
								double *collision_y, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		*collision_x += CUBE_SIZE;
		*collision_y -= CUBE_SIZE * tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		*collision_x -= CUBE_SIZE;
		*collision_y -= CUBE_SIZE / tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		*collision_x -= CUBE_SIZE;
		*collision_y += CUBE_SIZE * tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		*collision_x += CUBE_SIZE;
		*collision_y += CUBE_SIZE / tan(fmod(angle, RADIANS_90));
	}
}

void	dist_collision_vertical(t_collision *collision_v, t_world *world,
								double angle)
{
	double	collision_x;
	double	collision_y;
	int		range;

	get_first_intersection_vertical(world, &collision_x, &collision_y, angle);
	collision_v->x = collision_x;
	collision_v->y = collision_y;
	if (check_collision_vertical(world, collision_v, angle))
		return ;
	range = 0;
	while (range <= VIEW_DISTANCE)
	{
		get_next_intersection_vertical(&collision_x, &collision_y, angle);
		collision_v->x = collision_x;
		collision_v->y = collision_y;
		if (check_collision_vertical(world, collision_v, angle))
			return ;
		range++;
	}
}

void	get_next_intersection_horizontal(double *collision_x,
								double *collision_y, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		*collision_y -= CUBE_SIZE;
		*collision_x += CUBE_SIZE / tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		*collision_y -= CUBE_SIZE;
		*collision_x -= CUBE_SIZE * tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		*collision_y += CUBE_SIZE;
		*collision_x -= CUBE_SIZE / tan(fmod(angle, RADIANS_90));
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		*collision_y += CUBE_SIZE;
		*collision_x += CUBE_SIZE * tan(fmod(angle, RADIANS_90));
	}
}

void	dist_collision_horizontal(t_collision *collision_h, t_world *world,
									double angle)
{
	double	collision_y;
	double	collision_x;
	int		range;

	range = 0;
	get_first_intersection_horizontal(world, &collision_x, &collision_y,
										angle);
	collision_h->x = collision_x;
	collision_h->y = collision_y;
	if (check_collision_horizontal(world, collision_h, angle))
		return ;
	while (range <= VIEW_DISTANCE)
	{
		get_next_intersection_horizontal(&collision_x, &collision_y, angle);
		collision_h->x = collision_x;
		collision_h->y = collision_y;
		if (check_collision_horizontal(world, collision_h, angle))
			return ;
		range++;
	}
}

void	apply_color(t_world *world, t_collision *collision)
{
	if (collision->axis == 'v')
	{
		if (world->player.x <= (*collision).x)
			(*collision).color = EAST_COLOR;
		else
			(*collision).color = WEST_COLOR;
	}
	else
	{
		if (world->player.y <= (*collision).y)
			(*collision).color = SOUTH_COLOR;
		else
			(*collision).color = NORTH_COLOR;
	}
}

void	choose_closest_collision(t_collision *collision,
				t_collision collision_h, t_collision collision_v)
{
	if (collision_h.distance <= 0)
	{
		*collision = collision_v;
		collision->axis = 'v';
	}
	else if (collision_v.distance <= 0)
	{
		*collision = collision_h;
		collision->axis = 'h';
	}
	else if (collision_v.distance < collision_h.distance)
	{
		*collision = collision_v;
		collision->axis = 'v';
	}
	else
	{
		*collision = collision_h;
		collision->axis = 'h';
	}
}

void	cast_ray(t_collision *collision, t_world *world, double angle)
{
	t_collision *collision_v;
	t_collision	*collision_h;

	if (!(collision_v = (t_collision*)malloc(sizeof(t_collision) * 1)))
	{
		ft_putstr("Not enough memory\n");
		exit(0);
	}
	if (!(collision_h = (t_collision*)malloc(sizeof(t_collision) * 1)))
	{
		ft_putstr("Not enough memory\n");
		exit(0);
	}
	collision_initialize(collision_h);
	collision_initialize(collision_v);
	dist_collision_vertical(collision_v, world, angle);
	dist_collision_horizontal(collision_h, world, angle);
	choose_closest_collision(collision, *collision_h, *collision_v);
	collision->distance *= cos(angle - world->player.orientation);
}

int		collumn_length(double distance)
{
	int			length;

	length = (int)(CUBE_SIZE / (distance) *
				((WIN_WIDTH / 2) * tan(RADIANS_30)));
	if (length < 0)
		length = 0;
	if (length > WIN_HEIGHT)
		length = WIN_HEIGHT;
	return (length);
}

double	get_next_ray_angle(double player_orientation, int index)
{
	double		angle;

	angle = fmod((player_orientation - (FOV_RADIANS /
		(double)WIN_WIDTH / 2) + (FOV_RADIANS / 2) - (FOV_RADIANS * index /
		(double)WIN_WIDTH)), PI * 2);
	if (angle < 0)
		angle += PI * 2;
	return (angle);
}

void	render(t_world *world)
{
	int			i;
	double		angle;
	t_collision	*collision;

	if (!(collision = (t_collision*)malloc(sizeof(t_collision) * WIN_WIDTH)))
	{
		ft_putstr("Not enough memory\n");
		exit(0);
	}
	i = 0;
	while (i < WIN_WIDTH)
	{
		angle = get_next_ray_angle(world->player.orientation, i);
		cast_ray(&collision[i], world, angle);
		apply_color(world, &collision[i]);
		print_line(world, WIN_HEIGHT, i, BLACK);
		print_line(world, collumn_length(collision[i].distance), i,
											collision[i].color);
		i++;
	}
}

void	move_player_forward(int *player_x, int *player_y,
								double player_orientation, int player_speed)
{
	if (0 < player_orientation && player_orientation < RADIANS_90)
	{
		*player_y -= sin(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x += cos(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_90 < player_orientation && player_orientation < RADIANS_180)
	{
		*player_y -= cos(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x -= sin(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_180 < player_orientation && player_orientation < RADIANS_270)
	{
		*player_y += sin(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x -= cos(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_270 < player_orientation && player_orientation < RADIANS_360)
	{
		*player_y += cos(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x += sin(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
}

void	move_player_backward(int *player_x, int *player_y,
			double player_orientation, int player_speed)
{
	if (0 < player_orientation && player_orientation < RADIANS_90)
	{
		*player_y += sin(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x -= cos(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_90 < player_orientation && player_orientation < RADIANS_180)
	{
		*player_y += cos(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x += sin(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_180 < player_orientation && player_orientation < RADIANS_270)
	{
		*player_y -= sin(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x += cos(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
	if (RADIANS_270 < player_orientation && player_orientation < RADIANS_360)
	{
		*player_y -= cos(fmod(player_orientation, RADIANS_90)) * player_speed;
		*player_x -= sin(fmod(player_orientation, RADIANS_90)) * player_speed;
	}
}

void	key_handler1(t_world *world, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LSHIFT)
	{
		if (world->player.speed == 10)
			world->player.speed *= 10;
		else
			world->player.speed = 10;
	}
	if (event.key.keysym.sym == SDLK_x)
	{
		world->player.orientation = fmod((world->player.orientation - 0.04),
											PI * 2);
		if (world->player.orientation < 0)
			world->player.orientation += PI * 2;
	}
	if (event.key.keysym.sym == SDLK_z)
	{
		world->player.orientation = fmod((world->player.orientation + 0.04),
											PI * 2);
	}
	if (event.key.keysym.sym == SDLK_UP)
	{
		move_player_forward(&(world->player.x), &(world->player.y),
							world->player.orientation, world->player.speed);
	}
}

void	key_handler2(t_world *world, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_DOWN)
	{
		move_player_backward(&(world->player.x), &(world->player.y),
							world->player.orientation, world->player.speed);
	}
	if (event.key.keysym.sym == SDLK_LEFT)
		world->player.orientation = fmod((world->player.orientation +
											0.04), PI * 2);
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		world->player.orientation = fmod((world->player.orientation -
											0.04), PI * 2);
		if (world->player.orientation < 0)
			world->player.orientation += PI * 2;
	}
	if (event.key.keysym.sym == SDLK_e)
		map_editor(world);
}

int		wolf3d_handler(t_world *world, SDL_Surface *screen, SDL_Event event)
{
	if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	if (event.type == SDL_KEYDOWN)
	{
		key_handler1(world, event);
		key_handler2(world, event);
		render(world);
	}
	return (0);
}
