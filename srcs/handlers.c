/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2016/10/27 16:39:54 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

void	print_line(t_world *world, int length, int x)
{
	int y;

	y = 0;
	while(y < length)
		y++;
	while (y < WIN_HEIGHT && y < length * 2)
	{
		pixel_to_image(world->window.image, x, y, 16777215);
		y++;
	}
}

void	calc_a_horizontal(t_2d_p *a, float angle)
{
	//Add contition to eliminate if angle = 90 degrees
	if ((0 < angle && angle < RADIANS_90) || (RADIANS_90 < angle && angle < RADIANS_180))
		(*a).y = -1 * ((int)(CUBE_SIZE));
	else
		(*a).y = (int)(CUBE_SIZE);
	(*a).x = (int)(CUBE_SIZE) / tan(angle);
	//printf("[%d][%d][%f]\n", (*a).x, (*a).y, angle);
}

void	calc_a_vertical(t_2d_p *a, float angle)
{
	if ((0 < angle && angle < RADIANS_90) || (RADIANS_270 < angle && angle <= RADIANS_359))
		(*a).x = -1 * ((int)(CUBE_SIZE));
	else
		(*a).x = (int)(CUBE_SIZE);
	(*a).y = (int)(CUBE_SIZE) * tan(angle);
	//printf("[%d][%d][%f]\n", (*a).x, (*a).y, angle);
}

void	calc_inters_vertical(t_2d_p *pointInters, int playerX, int playerY,
							float angle)
{
	int y;
	int x;

	if ((0 < angle && angle < RADIANS_90) || (RADIANS_270 < angle && angle <= RADIANS_359))
		x = floor(playerX / (int)CUBE_SIZE) * (int)(CUBE_SIZE) + CUBE_SIZE;
	else
		x = floor(playerX / (int)CUBE_SIZE) * (int)(CUBE_SIZE) + (int)CUBE_SIZE;
	y = playerY + (playerX - x) / tan(angle);
	(*pointInters).y = y;
	(*pointInters).x = x;
}

void	calc_inters_horizontal(t_2d_p *pointInters, int playerX, int playerY,
							float angle)
{
	int y;
	int x;

	if ((0 < angle && angle < RADIANS_90) || (RADIANS_90 < angle && angle < RADIANS_180))
		y = floor(playerY / (int)CUBE_SIZE) * (int)(CUBE_SIZE) - 1;
	else
		y = floor(playerY / (int)CUBE_SIZE) * (int)(CUBE_SIZE) + (int)CUBE_SIZE;
	x = playerX + (playerY - y) / tan(angle);
	(*pointInters).y = y;
	(*pointInters).x = x;
}

void		dist_collision_vertical(t_collision *collision_v, t_world *world, float angle)
{
	t_2d_p pointInters;
	t_2d_p a;

	pointInters.x = 0;
	pointInters.y = 0;
	a.x = 0;
	a.y = 0;
	calc_inters_vertical(&pointInters, world->player.x, world->player.y, angle);
	if (world->map[pointInters.y / CUBE_SIZE][pointInters.x / CUBE_SIZE] == 1)
	{
		//printf("---[%f]----[%d][%d]---\n", angle, pointInters.y / CUBE_SIZE, pointInters.x / CUBE_SIZE);
		collision_v->distance = abs(world->player.x - pointInters.x) / cos(angle);
		collision_v->tile.y = pointInters.y / CUBE_SIZE;
		collision_v->tile.x = pointInters.x / CUBE_SIZE;
		return;
	}
	else
	{
		while(1)
		{
			calc_a_vertical(&a, angle);
			pointInters.y = pointInters.y + a.y;
			pointInters.x = pointInters.x + a.x;
			if ((pointInters.y / CUBE_SIZE) >= 0 && (pointInters.y / CUBE_SIZE) < MAP_HEIGHT && (pointInters.x / CUBE_SIZE) >= 0 && (pointInters.x / CUBE_SIZE) < MAP_WIDTH)
			{
				if(world->map[pointInters.y / CUBE_SIZE][pointInters.x / CUBE_SIZE] == 1)
				{
					//printf("---[%f]----[%d][%d]---\n", angle, pointInters.y / CUBE_SIZE, pointInters.x / CUBE_SIZE);
					collision_v->distance = abs(world->player.x - pointInters.x) / cos(angle);
					collision_v->tile.y = pointInters.y / CUBE_SIZE;
					collision_v->tile.x = pointInters.x / CUBE_SIZE;
					return;
				}
			}
			else
			{
				collision_v->distance = -1;
				return;
			}
		}
	}
}

void	dist_collision_horizontal(t_collision *collision_h, t_world *world, float angle)
{
	t_2d_p pointInters;
	t_2d_p a;

	pointInters.x = 0;
	pointInters.y = 0;
	a.x = 0;
	a.y = 0;
	
	calc_inters_horizontal(&pointInters, world->player.x, world->player.y, angle);
	if (world->map[pointInters.y / CUBE_SIZE][pointInters.x / CUBE_SIZE] == 1)
	{
		//printf("---[%f]----[%d][%d]---\n", angle, pointInters.y / CUBE_SIZE, pointInters.x / CUBE_SIZE);
		collision_h->distance = abs(world->player.x - pointInters.x) / cos(angle);
		collision_h->tile.y = pointInters.y / CUBE_SIZE;
		collision_h->tile.x = pointInters.x / CUBE_SIZE;
		//printf("%f\n", collision_h->distance);
		return;
	}
	else
	{
		while(1)
		{
			calc_a_horizontal(&a, angle);
			pointInters.y = pointInters.y + a.y;
			pointInters.x = pointInters.x + a.x;
			if ((pointInters.y / CUBE_SIZE) >= 0 && (pointInters.y / CUBE_SIZE) < MAP_HEIGHT && (pointInters.x / CUBE_SIZE) >= 0 && (pointInters.x / CUBE_SIZE) < MAP_WIDTH)
			{
				if(world->map[pointInters.y / CUBE_SIZE][pointInters.x / CUBE_SIZE] == 1)
				{
					//printf("---[%f]----[%d][%d]---\n", angle, pointInters.y / CUBE_SIZE, pointInters.x / CUBE_SIZE);
					collision_h->distance = abs(world->player.x - pointInters.x) / cos(angle);
					collision_h->tile.y = pointInters.y / CUBE_SIZE;
					collision_h->tile.x = pointInters.x / CUBE_SIZE;
						//printf("%f\n", collision_h->distance);
					return;
				}
			}
			else
			{
				collision_h->distance = -1;
				return;
			}
		}
	}
}

void	cast_ray(t_collision *collision, t_world *world, float angle)
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
	dist_collision_vertical(collision_v, world, angle);
	dist_collision_horizontal(collision_h, world, angle);
	//printf("[%f]   ", collision_h->distance);
	//printf("[%f]\n", collision_v->distance);
	if (collision_v->distance != -1 && collision_h->distance != -1)
	{
		if (collision_v->distance > collision_h->distance)
		{
			*collision = *collision_h;
			collision_h->distance = collision_h->distance * cos(world->player.orientation);
		}	
		else
		{
			*collision = *collision_v;
			collision_v->distance = collision_v->distance * cos(world->player.orientation);
		}
	}
	else if (collision_v->distance == -1)
		*collision = *collision_h;
	else
		*collision = *collision_v;
	printf("[%f]\n", collision->distance);

}

void	render(t_world *world)
{
	int			i;
	float		angle;
	t_collision	*collision;

	i = 0;
	angle = world->player.orientation + RADIANS_30;
	//printf("%f\n", angle);
	if (!(collision = (t_collision*)malloc(sizeof(t_collision) * WIN_WIDTH)))
	{
		ft_putstr("Not enough memory\n");
		exit(0);
	}
	//while (i < WIN_WIDTH)
	while (i < 10)
	{
		 cast_ray(&collision[i], world, angle);
		//get_distance(world->player.x, world->player.y, colision.x, collision.y);
	 	angle -= ((int)FOV_RADIANS / (float)WIN_WIDTH);
	 	i++;
	 }
	
	 i = 0;
	 while (i < WIN_WIDTH)
	 {
		 int length = (int)(64 / (collision[i].distance) * ((WIN_WIDTH / 2) * tan(RADIANS_30)));
		 //printf("[%f]", collision[i].distance);
		 //printf("[%d]", length);
		 print_line(world, length, i);
		 i++;
	 }
}

int	wolf3d_handler(t_world *world, SDL_Surface *screen, SDL_Event event)
{
	if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
    {
		//Quit the program
        return (1);
    }
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			world->player.orientation += 0.01;
			render(world);
		}
		else if (event.key.keysym.sym == SDLK_LEFT)
		{
			world->player.orientation -= 0.01;
			render(world);
		}
	}	
	return (0);
}