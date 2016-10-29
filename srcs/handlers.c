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
#include <SDL2/SDL.h>


void	wolf3d_handler(int ***map, SDL_Surface *screen, SDL_Event event)
{
	t_data *data;

	data = NULL;
	if (!(data = (t_data*)malloc(sizeof(t_data) * 1)))
	{
		ft_putstr("Not enough memory\n");
		exit(0);
	}
	if (event.type = SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP)
		pixel_to_image(screen, 50, 50, 16777215);
	}
	data->playerX = 96;
	data->playerY = 224;
	data->viewingAng = 90;
	//render(&data, map);
}