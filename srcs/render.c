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

#include "../libft/libft.h"
#include "../includes/wolf3d.h"
#include "../frameworks/SDL2.framework/Headers/SDL.h"

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
	free(collision);
}
