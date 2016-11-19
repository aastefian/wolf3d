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

	if ((0 < angle && angle < RADIANS_90) || (RADIANS_270 < angle && angle <= RADIANS_360))
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
/*
void		dist_collision_vertical(t_collision *collision_v, t_world *world, float angle)
{
	// TODO: handle left and right sides of the angle
	int collisionX = (world->player.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	int collisionY = world->player.y - (int) ((collisionX - world->player.x) * tan(angle));
			  ////printf("collision(%d, %d)\n", collisionX, collisionY);


	t_tile firstTile = getPointTile(collisionX, collisionY);

	if(firstTile.x >= 0 &&
	 firstTile.x < MAP_WIDTH &&
	  firstTile.y >= 0 &&
	  firstTile.y < MAP_HEIGHT &&
	  world->map[firstTile.y][firstTile.x]) {
		 	collision_v->distance = getDistance(world->player.x, collisionX, angle);
			//printf("distance %f\n", collision_v->distance);
		  	collision_v->tile.x = firstTile.x;
		  	collision_v->tile.y = firstTile.y;
			 // printf("delta %d cos %f dist %f dist2 %f\n", abs(world->player.x - collisionX),  cos(angle), collision_v->distance, (float)(abs(world->player.x - collisionX)) / cos(angle));
			  //printf("playerX %d, collisionX %d, collisionY %d, distance %f angle %f\n", world->player.x, collisionX, collisionY, collision_v->distance, angle);
		  return;
	  }
	  
	  while (1)
	  {
		  collisionX += 64;
		  collisionY += 64 * tan(angle);
		  //printf("collisionY After %d\n", collisionY);
		  firstTile = getPointTile(collisionX, collisionY);
		if(firstTile.x >= 0 &&
				firstTile.x < MAP_WIDTH &&
				firstTile.y >= 0 &&
				firstTile.y < MAP_HEIGHT &&
	  			world->map[firstTile.y][firstTile.x]) {
		 			collision_v->distance = getDistance(world->player.x, collisionX, angle);
					 //printf("distance %f\n", collision_v->distance);
		  			collision_v->tile.x = firstTile.x;
		  			collision_v->tile.y = firstTile.y;
		  			return;
		}
		break;
	  }
	
	// printf("tile (%d, %d)\n", firstTile.x, firstTile.y);
	// printf("tile %d\n", world->map[firstTile.y][firstTile.x]);
	// printf("angle %f\n", angle);
	// t_2d_p pointInters;
	// t_2d_p a;

	// pointInters.x = 0;
	// pointInters.y = 0;
	// a.x = 0;
	// a.y = 0;
	// calc_inters_vertical(&pointInters, world->player.x, world->player.y, angle);
	// if (world->map[pointInters.y / CUBE_SIZE][pointInters.x / CUBE_SIZE] == 1)
	// {
	// 	//printf("---[%f]----[%d][%d]---\n", angle, pointInters.y / CUBE_SIZE, pointInters.x / CUBE_SIZE);
	// 	collision_v->distance = abs(world->player.x - pointInters.x) / cos(angle);
	// 	collision_v->tile.y = pointInters.y / CUBE_SIZE;
	// 	collision_v->tile.x = pointInters.x / CUBE_SIZE;
	// 	return;
	// }
	// else
	// {
	// 	while(1)
	// 	{
	// 		calc_a_vertical(&a, angle);
	// 		pointInters.y = pointInters.y + a.y;
	// 		pointInters.x = pointInters.x + a.x;
	// 		if ((pointInters.y / CUBE_SIZE) >= 0 && (pointInters.y / CUBE_SIZE) < MAP_HEIGHT && (pointInters.x / CUBE_SIZE) >= 0 && (pointInters.x / CUBE_SIZE) < MAP_WIDTH)
	// 		{
	// 			if(world->map[pointInters.y / CUBE_SIZE][pointInters.x / CUBE_SIZE] == 1)
	// 			{
	// 				//printf("---[%f]----[%d][%d]---\n", angle, pointInters.y / CUBE_SIZE, pointInters.x / CUBE_SIZE);
	// 				collision_v->distance = abs(world->player.x - pointInters.x) / cos(angle);
	// 				collision_v->tile.y = pointInters.y / CUBE_SIZE;
	// 				collision_v->tile.x = pointInters.x / CUBE_SIZE;
	// 				return;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			collision_v->distance = -1;
	// 			return;
	// 		}
	// 	}
	// }
}
*/

void		dist_collision_vertical(t_collision *collision_v, t_world *world, float angle)
{
	int collisionX;
	int collisionY;
	// TODO: handle left and right sides of the angle
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
		printf("test %d\n", 2);	
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
	//exit(0);
	}                                                                                        
		//collisionY = world->player.y + (int) ((world->player.x - collisionX) * tan(fmod(angle, RADIANS_90)));
	//int collisionX = (world->player.x / CUBE_SIZE) * CUBE_SIZE;
	//int collisionY = world->player.y - (int) ((world->player.x - collisionX) / tan(fmod(angle, RADIANS_90)));
	

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
			//printf("distance %f\n", collision_v->distance);
		  	collision_v->tile.x = firstTile.x;
		  	collision_v->tile.y = firstTile.y;
			  //printf("collision(%d, %d)\n", collisionY, collisionX);
		  return;
	  }
	  
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

		  			return;
		}
		break;
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
		collisionY = floor(world->player.x / CUBE_SIZE) * CUBE_SIZE - 1;
		collisionX = world->player.x - (int)((world->player.y - collisionY) * tan(fmod(angle, RADIANS_90)));
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
		printf("Going Out Of Programmed Sequence\n");
		//exit(0);
	}
	
		//collisionY = floor(world->player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	
	//printf("angle %f\n", fmod(angle, RADIANS_90));
	//int collisionY = (world->player.y / CUBE_SIZE) * CUBE_SIZE;
	//int collisionX = world->player.x - (int)((world->player.y - collisionY) * tan(fmod(angle, RADIANS_90)));
	//if (angle < 0.785398)
	//printf("collision(%d, %d), distance %d\n", collisionX, collisionY, abs(world->player.y - collisionY) / cos(angle));
//if (angle >= 0.785398)
//		printf("collision(%d, %d) angle %f\n", collisionY / 64, collisionX / 64, angle);			  
	  //printf("collisionY %d collisionX %d playerY %d playerX %d tang %f\n---------\n", collisionY, collisionX, world->player.y, world->player.x, fmod(angle, RADIANS_90));

	t_tile firstTile = getPointTile(collisionX, collisionY);
	//printf("x %d, y %d, collisionX %d, collisionY %d\n", firstTile.x, firstTile.y, collisionX, collisionY);

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
			//printf("distance %f\n", collision_v->distance);
		  	collision_h->tile.x = firstTile.x;
		  	collision_h->tile.y = firstTile.y;
			 //printf("delta %d cos %f dist %f dist2 %f\n", abs(world->player.y - collisionY),  sin(angle), collision_h->distance, (abs(world->player.y - collisionY)) / sin(angle));
		  return;
	  }
	  
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
		  //printf("collisionY After %d\n", collisionY);
		  firstTile = getPointTile(collisionX, collisionY);
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
					 //printf("distance %f\n", collision_v->distance);
		  			collision_h->tile.x = firstTile.x;
		  			collision_h->tile.y = firstTile.y;
		  			return;
		}
		break;
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
	if (angle == 0)
	exit(0);
	collision_initialize(collision_h);
	collision_initialize(collision_v);
	 //printf("angle %f\n", angle);
	dist_collision_vertical(collision_v, world, angle);
	dist_collision_horizontal(collision_h, world, angle);
	//if (collision_h->distance <= 0 || collision_v->distance <= 0)
printf("vertical %f, horizontal %f angle %f real angle %f\n", collision_v->distance, collision_h->distance, angle, fmod(angle, RADIANS_90));
//printf("vertical(%d, %d) horizontal(%d, %d)\n", collision_v->tile.y, collision_v->tile.x, collision_h->tile.y, collision_h->tile.x);
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

	printf("Player orientation %f\n", world->player.orientation);
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
if (collision[i].distance <= 0 || collision[i].distance > WIN_HEIGHT)
{
	//printf("haha %f\n", collision[i].distance);	
	collision[i].distance = 0;
	//printf("haha %f\n", collision[i].distance);
}
		int length = (int)(64 / (collision[i].distance) * ((WIN_WIDTH / 2) * tan(RADIANS_30)));
		if (length < 0)
		{
			//printf("length %d\n", length);
			length = 10;
			
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
		
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			world->player.orientation = fmod((world->player.orientation - 0.04), M_PI * 2);
			if (world->player.orientation < 0)
				world->player.orientation += M_PI * 2;
			render(world);
		}
		else if (event.key.keysym.sym == SDLK_LEFT)
		{
			world->player.orientation = fmod((world->player.orientation + 0.04), M_PI * 2);
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