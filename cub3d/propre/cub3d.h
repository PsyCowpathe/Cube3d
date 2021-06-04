/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:12:33 by agirona           #+#    #+#             */
/*   Updated: 2021/05/14 19:01:08 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>

# define WIN_X 1920
# define WIN_Y 1080
# define NORTH "../textures/Nwall.xpm"
# define SOUTH "../textures/Swall.xpm"
# define EAST "../textures/Ewall.xpm"
# define WEST "../textures/Wwall.xpm"
# define SKY "../textures/sky.xpm"
# define SPRITE "../textures/sprite.xpm"
# define RED 0XFF0000
# define BLUE 0X0000FF
# define GREEN 0X00FF00
# define WHITE 0XFFFFFF
# define BLACK 0x000000
# define DIRT 0XB68831
//# define SKY 0X87CEFA
# define ROT 3
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT_TURN 123
# define KEY_RIGHT_TURN 124
# define KEY_ECHAP 53

typedef struct	s_xpm
{
	void	*img;
	int		*addr;
	int		bpp;
	int		endian;
	int		size_line;
	int		img_width;
	int		img_height;
}				t_xpm;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*addr;
	int		bits;
	int		endian;
	int		linelen;
	int		img_width;
	int		img_height;

	t_xpm	xpm[6];

	char	**map;
	int		mapy;
	float	fov;
	int		cubesize;
	int		proj;
	int		pheight;
	float	px;
	float	py;
	float	gap;
	float	looking;
	float	time;
	int		end;
	float	sneak;
	

	float	distance;
	float	hdist;
	float	vdist;
	float	horx;
	float	hory;
	float	vertx;
	float	verty;

	int		forward;
	int		right;
	int		left;
	int		backward;
	int		turnright;
	int		turnleft;
	int		lookup;
	int		lookdown;

	int		sprite;
	float	hdistsprite;
	float	vdistsprite;
	float	hspritex;
	float	vspritey;
	int		spritex;
	int		spritey;
	int		firstx;
	int		lastx;

	long long last_time;

	char	*bmpheader;
	int		screenshot;
	int		fd;
}				t_mlx;

int		init(t_mlx *data, char *str);

int		read_map(char *str, t_mlx *data);

#include <stdio.h>

void	get_distance(t_mlx *data);

void	print_column(t_mlx *data, int x, int height, int texture);
void	clear_win(t_mlx *data);
void	sky_box(t_mlx *data);
void	sprite(t_mlx *data, int x, float dist);


float	*rotate(float *centerxy, float *pointxy, float angle);


int		keyrelease(int key, t_mlx *data);
int		keypress(int key, t_mlx *data);


int		bmp_header(t_mlx *data, char **header);
void	take_screenshot(t_mlx *data);

int		event(t_mlx *data);
#endif
