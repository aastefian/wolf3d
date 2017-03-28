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
#include "../frameworks/SDL2.framework/Headers/SDL.h"

void	collision_initialize(t_collision *collision)
{
	collision->distance = 0;
	collision->tile.x = 0;
	collision->tile.y = 0;
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

void	dist_collision_vertical(t_collision *collision_v, t_world *world,
								double angle)
{
	int		range;

	get_first_intersection_vertical(collision_v, world->player.x,
													world->player.y, angle);
	if (check_collision_vertical(world, collision_v, angle))
		return ;
	range = 0;
	while (range <= VIEW_DISTANCE)
	{
		get_next_intersection_vertical(collision_v, angle);
		if (check_collision_vertical(world, collision_v, angle))
			return ;
		range++;
	}
}

void	dist_collision_horizontal(t_collision *collision_h, t_world *world,
									double angle)
{
	int		range;

	range = 0;
	get_first_intersection_horizontal(collision_h, world->player.x,
										world->player.y, angle);
	if (check_collision_horizontal(world, collision_h, angle))
		return ;
	while (range <= VIEW_DISTANCE)
	{
		get_next_intersection_horizontal(collision_h, angle);
		if (check_collision_horizontal(world, collision_h, angle))
			return ;
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
	choose_closest_collision(collision, *collision_h, *collision_v);
	collision->distance *= cos(angle - world->player.orientation);
	free(collision_v);
	free(collision_h);
}
