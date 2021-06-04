/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:47:15 by agirona           #+#    #+#             */
/*   Updated: 2021/05/20 16:54:14 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//tmp
#include <stdio.h>
# define NORTH "../../textures/Nwall.xpm"
# define SOUTH "../../textures/Swall.xpm"
# define EAST "../../textures/Ewall.xpm"
# define WEST "../../textures/Wwall.xpm"
# define SPRITE "../../textures/sprite.xpm"
# define DIRT 0xB68831
# define ROT 3
//tmp

# include "../../libft/libft.h"
# include "../../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIN_X 1920
# define WIN_Y 1080
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
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

typedef struct	s_sprite
{
	int			x;
	int			y;
	float		distance;
	int			visible;
	float		angle;
}				t_sprite;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*addr;
	int		bits;
	int		endian;
	int		linelen;
	t_xpm	xpm[5];

	char	**map;
	int		mapy;
	float	looking;
	float	gap;
	float	px;
	float	py;
	float	fov;
	int		cubesize;
	int		proj;
	int		pheight;

	float	hdist;
	float	vdist;
	float	*alldist;
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
	int		end;

	char	*bmpheader;
	int		fd;
	int		screenshot;
}				t_mlx;

//init

int		init(t_mlx *data, char *str);

//parsing

int		read_map(t_mlx *data, char *str);

//racasting

void	get_distance(t_mlx *data);

//sprite

int		sprite(t_mlx *data);

//get_key

int		keypress(int key, t_mlx *data);
int		keyrelease(int key, t_mlx *data);
void	event(t_mlx *data);

//event.c

void	moov_player(t_mlx *data);
void	moov_camera(t_mlx *data);
void	exit_game(t_mlx *data);

//draw

void	clear_win(t_mlx *data);
void	print_column(t_mlx *data, int x, int height, int texture);

//screenshot

int		bmp_header(t_mlx *data, char **header);
void	take_screenshot(t_mlx *data);

//utility

float	*rotate(float *centerxy, float *pointxy, float angle);

#endif
