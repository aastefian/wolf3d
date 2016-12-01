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

void	print_line(t_world *world, int length, int x, int color)
{
	int y;

	y = 0;
	while (y < WIN_HEIGHT - (WIN_HEIGHT - length) / 2)
	{
		if(y < (WIN_HEIGHT - length) / 2) {
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

t_tile getPointTile(int x, int y){
	t_tile pointTile;

	pointTile.x = floor(x / CUBE_SIZE);
	pointTile.y = floor(y / CUBE_SIZE);

	return (pointTile);
}

float getDistance(int x1,int x2,float angle){
	return abs(x1 - x2) / cos(angle);
}

float getDistanceHorizontal(int x1,int x2,float angle){
	return (abs(x1 - x2) / sin(angle));
}

void		dist_collision_vertical(t_collision *collision_v, t_world *world, float angle)
{
	int collisionX;
	int collisionY;
	// If angle to the right x always goes to right and +1
	if (0 < angle && angle < RADIANS_90)
	{
		collisionX = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collisionY = world->player.y - (int)((collisionX - world->player.x) * tan(fmod(angle, RADIANS_90)));
	}
	else if(RADIANS_90 < angle && angle < RADIANS_180)
	{
		collisionX = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE - 1;
		collisionY = world->player.y - (int)((world->player.x - collisionX) / tan(fmod(angle, RADIANS_90)));
	}
	else if(RADIANS_180 < angle && angle < RADIANS_270)
	{
		collisionX = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE - 1;
		collisionY = world->player.y + (int)((world->player.x - collisionX) * tan(fmod(angle, RADIANS_90)));

	}
	else if(RADIANS_270 < angle && angle < RADIANS_360)
	{
		collisionX = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collisionY = world->player.y + (int)((collisionX - world->player.x) / tan(fmod(angle, RADIANS_90)));
	}
	else
		//collisionX = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE - 1;
	{
	printf("Going Out Of Programmed Sequence\n");
	exit(0);
	}                                                                                        

	t_tile firstTile = getPointTile(collisionX, collisionY);

	if(firstTile.x >= 0 &&
	 firstTile.x < MAP_WIDTH &&
	  firstTile.y >= 0 &&
	  firstTile.y < MAP_HEIGHT &&
	  world->map[firstTile.y][firstTile.x]) {
		  if (0 < angle && angle < RADIANS_90)
		 		collision_v->distance = getDistance(world->player.x, collisionX, fmod(angle, RADIANS_90));		 		
		 else if(RADIANS_90 < angle && angle < RADIANS_180)
			 	collision_v->distance = getDistanceHorizontal(world->player.x, collisionX, fmod(angle, RADIANS_90));
		 else if(RADIANS_180 < angle && angle < RADIANS_270)
			 	collision_v->distance = getDistance(world->player.x, collisionX, fmod(angle, RADIANS_90));
		else if(RADIANS_270 < angle && angle < RADIANS_360)
				collision_v->distance = getDistanceHorizontal(world->player.x, collisionX, fmod(angle, RADIANS_90));
		  	collision_v->tile.x = firstTile.x;
		  	collision_v->tile.y = firstTile.y;
			  //printf("collision(%d, %d)\n", collisionY, collisionX);
		  return;
	  }
	  int w = 0;
	  while (1)
	  {
		if (0 < angle && angle < RADIANS_90)
		{
			collisionX += 64;
			collisionY -= CUBE_SIZE * tan(fmod(angle, RADIANS_90));
		}	
		else if(RADIANS_90 < angle && angle < RADIANS_180)
		{
			collisionX -= 64;
			collisionY -= CUBE_SIZE / tan(fmod(angle, RADIANS_90));
			
		}
		else if(RADIANS_180 < angle && angle < RADIANS_270)
		{
			collisionX -= 64;
			collisionY += CUBE_SIZE * tan(fmod(angle, RADIANS_90));	
		}
		else if(RADIANS_270 < angle && angle < RADIANS_360)
		{
			collisionX += 64;
			collisionY += CUBE_SIZE / tan(fmod(angle, RADIANS_90));	
		}
		else
		{
			printf("Going Out Of Programmed Sequence\n");
			//exit(0);
		}

		  
		  //printf("collisionY After %d\n", collisionY);
		  firstTile = getPointTile(collisionX, collisionY);
		  
		 
		if(firstTile.x >= 0 &&
				firstTile.x < MAP_WIDTH &&
				firstTile.y >= 0 &&
				firstTile.y < MAP_HEIGHT &&
	  			world->map[firstTile.y][firstTile.x]) {
		 			if (0 < angle && angle < RADIANS_90)
		 				collision_v->distance = getDistance(world->player.x, collisionX, fmod(angle, RADIANS_90));		 		
					 else if(RADIANS_90 < angle && angle < RADIANS_180)
					 	collision_v->distance = getDistanceHorizontal(world->player.x, collisionX, fmod(angle, RADIANS_90));
					 else if(RADIANS_180 < angle && angle < RADIANS_270)
			 			collision_v->distance = getDistance(world->player.x, collisionX, fmod(angle, RADIANS_90));
					 else if(RADIANS_270 < angle && angle < RADIANS_360)
						collision_v->distance = getDistanceHorizontal(world->player.x, collisionX, fmod(angle, RADIANS_90));
					 //printf("distance %f\n", collision_v->distance);
		  			collision_v->tile.x = firstTile.x;
		  			collision_v->tile.y = firstTile.y;
//printf("collisionY %d collisionX %d playerY %d playerX %d tang %f\n---------\n", collisionY, collisionX, world->player.y, world->player.x, fmod(angle, RADIANS_90));					  					  
					  
					 // if (angle < 0.785398)
		//printf("collision(%d, %d) angle %f\n", collisionY / 64, collisionX / 64, angle);			  
//printf("y %d, x %d, collisionX %d, collisionY %d distance %f\n", firstTile.y, firstTile.x, collisionX, collisionY, collision_v->distance);

		  			return;
		}
		if (w == 4)
			break;
		w++;
	  }
	  
	  
}

void	dist_collision_horizontal(t_collision *collision_h, t_world *world, float angle)
{
	int collisionY;
	int collisionX;

	if (0 < angle && angle < RADIANS_90)
	{
		collisionY = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE - 1;
		collisionX = world->player.x + (int)((world->player.y - collisionY) / tan(fmod(angle, RADIANS_90)));
	}
	else if(RADIANS_90 < angle && angle < RADIANS_180)
	{
		collisionY = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE - 1;
		collisionX = world->player.x - (int)((world->player.y - collisionY) * tan(fmod(angle, RADIANS_90)));
		if (angle <= 2.902897 && angle >= 2.69)
			printf("collisionY %d collisionX %d playerY %d playerX %d angle %f collisionY real %f\n---------\n", collisionY, collisionX, world->player.y, world->player.x, angle, tan(fmod(angle, RADIANS_90)));				
	}
	else if(RADIANS_180 < angle && angle < RADIANS_270)
	{
		collisionY = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collisionX = world->player.x - (int)((collisionY - world->player.y) / tan(fmod(angle, RADIANS_90)));	
	}
	else if(RADIANS_270 < angle && angle < RADIANS_360)
	{
		collisionY = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		collisionX = world->player.x + (int)((collisionY - world->player.y) * tan(fmod(angle, RADIANS_90)));	
	}
	else
	{
		printf("Going Out Of Programmed Sequence \n");
		//exit(0);
	}
	
	t_tile firstTile = getPointTile(collisionX, collisionY);

	if(firstTile.x >= 0 &&
	 firstTile.x < MAP_WIDTH &&
	  firstTile.y >= 0 &&
	  firstTile.y < MAP_HEIGHT &&
	  world->map[firstTile.y][firstTile.x]) {
		if (0 < angle && angle < RADIANS_90)
			 collision_h->distance = getDistanceHorizontal(world->player.y, collisionY, fmod(angle, RADIANS_90));
		else if(RADIANS_90 < angle && angle < RADIANS_180)
			collision_h->distance = getDistance(world->player.y, collisionY, fmod(angle, RADIANS_90));
		else if(RADIANS_180 < angle && angle < RADIANS_270)
			collision_h->distance = getDistanceHorizontal(world->player.y, collisionY, fmod(angle, RADIANS_90));
		else if(RADIANS_270 < angle && angle < RADIANS_360)
			collision_h->distance = getDistance(world->player.y, collisionY, fmod(angle, RADIANS_90));
			//printf("distance %f\n", collision_h->distance);
		  	collision_h->tile.x = firstTile.x;
		  	collision_h->tile.y = firstTile.y;
		  return;
	  }
	  int w = 0;
	  while (1)
	  {
		if (0 < angle && angle < RADIANS_90)
		{
		  	collisionY -= 64;
			collisionX += CUBE_SIZE / tan(fmod(angle, RADIANS_90));
		}
		else if(RADIANS_90 < angle && angle < RADIANS_180)
		{
			collisionY -= 64;
			collisionX -= CUBE_SIZE * tan(fmod(angle, RADIANS_90));
		}
		else if(RADIANS_180 < angle && angle < RADIANS_270)
		{
			collisionY += 64;
			collisionX -= CUBE_SIZE / tan(fmod(angle, RADIANS_90));	
		}
		else if(RADIANS_270 < angle && angle < RADIANS_360)
		{
			collisionY += 64;
			collisionX += CUBE_SIZE * tan(fmod(angle, RADIANS_90));	
		}
		else
		{
			printf("Going Out Of Programmed Sequence\n");
			//exit(0);
		}
		  //printf("collisionY %d collisionX %d\n", collisionY, collisionX);
		  firstTile = getPointTile(collisionX, collisionY);
		 //printf("y: %d x: %d\n", firstTile.y, firstTile.x);
		if(firstTile.x >= 0 &&
				firstTile.x < MAP_WIDTH &&
				firstTile.y >= 0 &&
				firstTile.y < MAP_HEIGHT &&
	  			world->map[firstTile.y][firstTile.x]) {
		 	if (0 < angle && angle < RADIANS_90)
				collision_h->distance = getDistanceHorizontal(world->player.y, collisionY, fmod(angle, RADIANS_90));
			else if(RADIANS_90 < angle && angle < RADIANS_180)
				collision_h->distance = getDistance(world->player.y, collisionY, fmod(angle, RADIANS_90));
			else if(RADIANS_180 < angle && angle < RADIANS_270)
		 		collision_h->distance = getDistanceHorizontal(world->player.y, collisionY, fmod(angle, RADIANS_90));
			else if(RADIANS_270 < angle && angle < RADIANS_360)
				collision_h->distance = getDistance(world->player.y, collisionY, fmod(angle, RADIANS_90));
					//printf("distance %f\n", collision_h->distance);
		 collision_h->tile.x = firstTile.x;
		 collision_h->tile.y = firstTile.y;
		 
		 return;
		}
		if (w == 4)
			break;
		w++;
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
	collision_initialize(collision_h);
	collision_initialize(collision_v);
	 //printf("angle %f\n", angle);
	dist_collision_vertical(collision_v, world, angle);
	dist_collision_horizontal(collision_h, world, angle);
	//printf("vertical %f, horizontal %f\n", collision_v->distance, collision_h->distance);
	//if (collision_h->distance <= 0 || collision_v->distance <= 0)
//printf("vertical %f, horizontal %f angle %f real angle %f\n", collision_v->distance, collision_h->distance, angle, fmod(angle, RADIANS_90));
//printf("vertical(%d, %d) horizontal(%d, %d) angle %f\n", collision_v->tile.y, collision_v->tile.x, collision_h->tile.y, collision_h->tile.x, angle);
if (collision_h->distance <= 0)
	*collision = *collision_v;
else if (collision_v->distance <= 0)
	*collision = *collision_h;
else if (collision_v->distance < collision_h->distance)
		*collision = *collision_v;
else
		*collision = *collision_h;

		collision->distance *= cos(angle - world->player.orientation);
//printf("collision (%d, %d) = %d angle %f\n", collision->tile.y, collision->tile.x, world->map[collision->tile.y][collision->tile.x], angle);
}

void	render(t_world *world)
{
	int			i;
	float		angle;
	t_collision	*collision;

	//printf("Player orientation %f\n", world->player.orientation);
	//		printf("y: %d x: %d\n", world->player.y, world->player.x);						
	
	// TODO: free
	if (!(collision = (t_collision*)malloc(sizeof(t_collision) * WIN_WIDTH)))
	{
		ft_putstr("Not enough memory\n");
		exit(0);
	}

	i = 0;
	while (i < WIN_WIDTH)
	{
		angle = fmod((world->player.orientation - FOV_RADIANS / (float) WIN_WIDTH / 2 + FOV_RADIANS/2 - FOV_RADIANS * i / (float) WIN_WIDTH), M_PI * 2);
		if (angle < 0)
				angle += M_PI * 2; 
		//printf("angle %f\n", angle);
	 	cast_ray(&collision[i], world, angle);
//printf("collision[%d]->distance %f\n", i, collision[i].distance);	
//printf("distance %d\n", collision[i].distance);		 
		int length = (int)(64 / (collision[i].distance) * ((WIN_WIDTH / 2) * tan(RADIANS_30)));
		if (length < 0)
		{
			//printf("length %d distance %f angle %f\n", length, collision[i].distance, angle);
			length = 3;	
		}
		print_line(world, WIN_HEIGHT, i, BLACK);
		print_line(world, length, i, RED);		
	 	i++;
	 }
}

int	wolf3d_handler(t_world *world, SDL_Surface *screen, SDL_Event event)
{
	if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
    {
		char end[80]= "------------------------------\nEnd of log\n------------------------------\n";
		//Quit the program

		printf("%s", end);
        return (1);
    }
	if (event.type == SDL_KEYDOWN)
	{
		
		if (event.key.keysym.sym == SDLK_x)
		{
			world->player.orientation = fmod((world->player.orientation - 0.04), M_PI * 2);
			if (world->player.orientation < 0)
				world->player.orientation += M_PI * 2;
			render(world);
		}
		if (event.key.keysym.sym == SDLK_z)
		{
			world->player.orientation = fmod((world->player.orientation + 0.04), M_PI * 2);
			render(world);
		}
		if (event.key.keysym.sym == SDLK_UP)
		{
			world->player.y -= 2;
			render(world);
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			world->player.y += 2;
			render(world);
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			world->player.x -= 2;
			render(world);
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			world->player.x += 2;
			render(world);
		}
		/*
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			world->player.x += 1;
			render(world);
		}
		else if (event.key.keysym.sym == SDLK_LEFT)
		{
			world->player.x -= 1;			
			render(world);
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			world->player.y -= 2;			
			render(world);
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			world->player.y += 2;			
			render(world);
		}
		*/
	}

	return (0);
}