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

void	get_first_intersection_vertical(double *collision_x, double *collision_y, int player_x, int player_y, double angle)
{
	if (0 < angle && angle < RADIANS_90)
	{
		*collision_x = floor(player_x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		*collision_y = player_y - ((*collision_x - player_x) * tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		*collision_x = floor(player_x / CUBE_SIZE) * CUBE_SIZE - 1;
		*collision_y = player_y - ((player_x - *collision_x) / tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		*collision_x = floor(player_x / CUBE_SIZE) * CUBE_SIZE - 1;
		*collision_y = player_y + ((player_x - *collision_x) * tan(fmod(angle, RADIANS_90)));

	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		*collision_x = floor(player_x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		*collision_y = player_y + ((*collision_x - player_x) / tan(fmod(angle, RADIANS_90)));
	}
}

int 	check_collision_vertical(t_collision *collision_v,  double collision_x, double collision_y, int player_x, int **map, double angle)
{
	t_tile first_tile;
	
	first_tile = get_point_tile(collision_x, collision_y);
	if (first_tile.x >= 0 && first_tile.x < MAP_WIDTH && first_tile.y >= 0 &&
		first_tile.y < MAP_HEIGHT && map[first_tile.y][first_tile.x])
	{
		if (0 < angle && angle < RADIANS_90)
			collision_v->distance = get_distance_cos(player_x, collision_x, fmod(angle, RADIANS_90));
		else if (RADIANS_90 < angle && angle < RADIANS_180)
			collision_v->distance = get_distance_sin(player_x, collision_x, fmod(angle, RADIANS_90));
		else if (RADIANS_180 < angle && angle < RADIANS_270)
			collision_v->distance = get_distance_cos(player_x, collision_x, fmod(angle, RADIANS_90));
		else if (RADIANS_270 < angle && angle < RADIANS_360)
			collision_v->distance = get_distance_sin(player_x, collision_x, fmod(angle, RADIANS_90));
		collision_v->tile.x = first_tile.x;
		collision_v->tile.y = first_tile.y;
		collision_v->x = collision_x;
		collision_v->y = collision_y;
		return (1);
	}
	return (0);
}

void	dist_collision_vertical(t_collision *collision_v, t_world *world, double angle)
{
	double	collision_x;
	double	collision_y;
	
	get_first_intersection_vertical(&collision_x, &collision_y, world->player.x, world->player.y, angle);
	if (check_collision_vertical(collision_v, collision_x, collision_y, world->player.x, world->map, angle))
		return;

	  int range = 0;
	  while (1)
	  {
		if (0 < angle && angle < RADIANS_90)
		{
			collision_x += CUBE_SIZE;
			collision_y -= CUBE_SIZE * tan(fmod(angle, RADIANS_90));
		}	
		else if (RADIANS_90 < angle && angle < RADIANS_180)
		{
			collision_x -= CUBE_SIZE;
			collision_y -= CUBE_SIZE / tan(fmod(angle, RADIANS_90));
		}
		else if (RADIANS_180 < angle && angle < RADIANS_270)
		{
			collision_x -= CUBE_SIZE;
			collision_y += CUBE_SIZE * tan(fmod(angle, RADIANS_90));
		}
		else if (RADIANS_270 < angle && angle < RADIANS_360)
		{
			collision_x += CUBE_SIZE;
			collision_y += CUBE_SIZE / tan(fmod(angle, RADIANS_90));
		}
		if (check_collision_vertical(collision_v, collision_x, collision_y, world->player.x, world->map, angle))
			return;
		if (range == VIEW_DISTANCE)
			break;
		range++;
	  }
}

void	dist_collision_horizontal(t_collision *collision_h, t_world *world, double angle)
{
	double collision_y;
	double collision_x;

	if (0 < angle && angle < RADIANS_90)
	{
		collision_y = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE - 1;
		collision_x = world->player.x + ((world->player.y - collision_y) / tan(fmod(angle, RADIANS_90)));
	}
	else if (RADIANS_90 < angle && angle < RADIANS_180)
	{
		collision_y = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE - 1;
		collision_x = world->player.x - ((world->player.y - collision_y) * tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_180 < angle && angle < RADIANS_270)
	{
		collision_y = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collision_x = world->player.x - ((collision_y - world->player.y) / tan(fmod(angle, RADIANS_90))) + 1;
	}
	else if (RADIANS_270 < angle && angle < RADIANS_360)
	{
		collision_y = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collision_x = world->player.x + ((collision_y - world->player.y) * tan(fmod(angle, RADIANS_90)));
	}
	t_tile first_tile = get_point_tile(collision_x, collision_y);
	if (first_tile.x >= 0 &&
	 first_tile.x < MAP_WIDTH &&
	  first_tile.y >= 0 &&
	  first_tile.y < MAP_HEIGHT &&
	  world->map[first_tile.y][first_tile.x]) {
		if (0 < angle && angle < RADIANS_90)
			 collision_h->distance = get_distance_sin(world->player.y, collision_y, fmod(angle, RADIANS_90));
		else if (RADIANS_90 < angle && angle < RADIANS_180)
			collision_h->distance = get_distance_cos(world->player.y, collision_y, fmod(angle, RADIANS_90));
		else if (RADIANS_180 < angle && angle < RADIANS_270)
			collision_h->distance = get_distance_sin(world->player.y, collision_y, fmod(angle, RADIANS_90));
		else if (RADIANS_270 < angle && angle < RADIANS_360)
			collision_h->distance = get_distance_cos(world->player.y, collision_y, fmod(angle, RADIANS_90));
		  	collision_h->tile.x = first_tile.x;
		  	collision_h->tile.y = first_tile.y;
			collision_h->x = collision_x;
			collision_h->y = collision_y;
		  return;
	  }
	  int range = 0;
	  while (1)
	  {
		if (0 < angle && angle < RADIANS_90)
		{
		  	collision_y -= CUBE_SIZE;
			collision_x += CUBE_SIZE / tan(fmod(angle, RADIANS_90));
		}
		else if (RADIANS_90 < angle && angle < RADIANS_180)
		{
			collision_y -= CUBE_SIZE;
			collision_x -= CUBE_SIZE * tan(fmod(angle, RADIANS_90));
		}
		else if (RADIANS_180 < angle && angle < RADIANS_270)
		{
			collision_y += CUBE_SIZE;
			collision_x -= CUBE_SIZE / tan(fmod(angle, RADIANS_90));
		}
		else if (RADIANS_270 < angle && angle < RADIANS_360)
		{
			collision_y += CUBE_SIZE;
			collision_x += CUBE_SIZE * tan(fmod(angle, RADIANS_90));
		}
		 first_tile = get_point_tile(collision_x, collision_y);
		if (first_tile.x >= 0 &&
				first_tile.x < MAP_WIDTH &&
				first_tile.y >= 0 &&
				first_tile.y < MAP_HEIGHT &&
	  			world->map[first_tile.y][first_tile.x]) {
		 	if (0 < angle && angle < RADIANS_90)
				collision_h->distance = get_distance_sin(world->player.y, collision_y, fmod(angle, RADIANS_90));
			else if (RADIANS_90 < angle && angle < RADIANS_180)
				collision_h->distance = get_distance_cos(world->player.y, collision_y, fmod(angle, RADIANS_90));
			else if (RADIANS_180 < angle && angle < RADIANS_270)
		 		collision_h->distance = get_distance_sin(world->player.y, collision_y, fmod(angle, RADIANS_90));
			else if (RADIANS_270 < angle && angle < RADIANS_360)
				collision_h->distance = get_distance_cos(world->player.y, collision_y, fmod(angle, RADIANS_90));
		 collision_h->tile.x = first_tile.x;
		 collision_h->tile.y = first_tile.y;
		 collision_h->x = collision_x;
		 collision_h->y = collision_y;
		 return;
		}
		if (range == VIEW_DISTANCE)
			break;
		range++;
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
	if (collision_h->distance <= 0)
	{
		*collision = *collision_v;
		if (world->player.x <= (*collision).x)
			(*collision).color = EAST_COLOR;
		else
			(*collision).color = WEST_COLOR;
	}
	else if (collision_v->distance <= 0)
	{
		*collision = *collision_h;
		if (world->player.y <= (*collision).y)
			(*collision).color = SOUTH_COLOR;
		else
			(*collision).color = NORTH_COLOR;
	}
	else if (collision_v->distance < collision_h->distance)
	{
		*collision = *collision_v;
		if (world->player.x <= (*collision).x)
			(*collision).color = EAST_COLOR;
		else
			(*collision).color = WEST_COLOR;
	}
	else
	{
		*collision = *collision_h;
		if (world->player.y <= (*collision).y)
			(*collision).color = SOUTH_COLOR;
		else
			(*collision).color = NORTH_COLOR;
	}
	collision->distance *= cos(angle - world->player.orientation);
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
		angle = fmod((world->player.orientation - (FOV_RADIANS / (double) WIN_WIDTH / 2) + (FOV_RADIANS/2) - (FOV_RADIANS * i / (double) WIN_WIDTH)), PI * 2);
		if (angle < 0)
				angle += PI * 2;
	 	cast_ray(&collision[i], world, angle);
		int length = (int)(CUBE_SIZE / (collision[i].distance) * ((WIN_WIDTH / 2) * tan(RADIANS_30)));
		if (length < 0 || length > WIN_HEIGHT)
			length = WIN_HEIGHT;
		print_line(world, WIN_HEIGHT, i, BLACK);
		print_line(world, length, i , collision[i].color);
	 	i++;
	 }	 
}

void	move_player_forward(int *playerX, int *playerY, double playerOrientation, int playerSpeed)
{
	if (0 < playerOrientation && playerOrientation < RADIANS_90)
	{
		*playerY -= sin(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
		*playerX += cos(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
	}
	else if (RADIANS_90 < playerOrientation && playerOrientation < RADIANS_180)
	{
		*playerY -= cos(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
		*playerX -= sin(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
	}
	else if (RADIANS_180 < playerOrientation && playerOrientation < RADIANS_270)
	{
		*playerY += sin(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
		*playerX -= cos(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
	}
	else if (RADIANS_270 < playerOrientation && playerOrientation < RADIANS_360)
	{
		*playerY += cos(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
		*playerX += sin(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
	}
}

void	move_player_backward(int *playerX, int *playerY, double playerOrientation, int playerSpeed)
{
	if (0 < playerOrientation && playerOrientation < RADIANS_90)
	{
		*playerY += sin(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
		*playerX -= cos(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
	}
	else if (RADIANS_90 < playerOrientation && playerOrientation < RADIANS_180)
	{
		*playerY += cos(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
		*playerX += sin(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
	}
	else if (RADIANS_180 < playerOrientation && playerOrientation < RADIANS_270)
	{
		*playerY -= sin(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
		*playerX += cos(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
	}
	else if (RADIANS_270 < playerOrientation && playerOrientation < RADIANS_360)
	{
		*playerY -= cos(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
		*playerX -= sin(fmod(playerOrientation, RADIANS_90)) * playerSpeed;
	}
}

int		wolf3d_handler(t_world *world, SDL_Surface *screen, SDL_Event event)
{
	if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        return (1);
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_LSHIFT)
		{
			if (world->player.speed == 10)
				world->player.speed *= 10;
			else
				world->player.speed = 10;
			render(world);
		}
		if (event.key.keysym.sym == SDLK_x)
		{
			world->player.orientation = fmod((world->player.orientation - 0.04), PI * 2);
			if (world->player.orientation < 0)
				world->player.orientation += PI * 2;
			render(world);
		}
		if (event.key.keysym.sym == SDLK_z)
		{
			world->player.orientation = fmod((world->player.orientation + 0.04), PI * 2);
			render(world);
		}
		if (event.key.keysym.sym == SDLK_UP)
		{
			move_player_forward(&(world->player.x), &(world->player.y), world->player.orientation, world->player.speed);
			render(world);
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			move_player_backward(&(world->player.x), &(world->player.y), world->player.orientation, world->player.speed);
			render(world);
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			world->player.orientation = fmod((world->player.orientation +
												0.04), PI * 2);	
			render(world);
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			world->player.orientation = fmod((world->player.orientation -
												0.04), PI * 2);
			if (world->player.orientation < 0)
				world->player.orientation += PI * 2;
			render(world);
		}
		if (event.key.keysym.sym == SDLK_e)
			map_editor(world);
	}
	return (0);
}
