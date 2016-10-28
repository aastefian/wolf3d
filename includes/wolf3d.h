/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:50:12 by svilau            #+#    #+#             */
/*   Updated: 2016/10/21 11:56:22 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_3D_H
# define _WOLF_3D_H
# define WIN_WIDTH 1280
# define WIN_HEIGHT 800
# define WIN_BPP 32
# define MAP_WIDTH 5
# define MAP_HEIGHT 6
#define CUBE_SIZE 64

typedef struct		s_mlx
{
	void *mlx;
	void *win;
}					t_mlx;

typedef struct		s_img
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data;
}					t_img;

typedef struct		s_keys
{
	int left;
	int right;
	int up;
	int down;
}					t_keys;

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

typedef struct		s_data
{
	t_mlx	mini_l;
	t_img	img;
	t_keys	keys_pushed;
	float	viewingAng;
	int		playerX;
	int		playerY;
}					t_data;

void	wolf3d_handler(int ***map, t_mlx mini_l, t_img img);
void	load_map(int ***map, char *map_name);

#endif
