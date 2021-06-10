/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:47:15 by agirona           #+#    #+#             */
/*   Updated: 2021/06/10 20:49:35 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//tmp
# include <stdio.h>
# define NORTH "textures/Nwall.xpm"
# define SOUTH "textures/Swall.xpm"
# define EAST "textures/Ewall.xpm"
# define WEST "textures/Wwall.xpm"
# define SPRITE "textures/sprite.xpm"
# define SKY "textures/sky.xpm"
# define HAND "textures/hand.xpm"
# define REV_SPRITE "textures/reverse_sprite.xpm"
# define DIRT 0xB68831
# define ROT 3
//tmp

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>
# include <sys/time.h>
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
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_SPACE 49
# define KEY_SCREENSHOT 105
# define KEY_G 5
# define KEY_PLUS 69

typedef struct s_scale
{
	int		winx;
	int		winy;
	float	x;
	float	y;
	int		txt;
	float	hdist;
	float	vdist;
	float	dist;
	int		len;
}				t_scale;

typedef struct s_xpm
{
	void	*img;
	int		*addr;
	int		bpp;
	int		endian;
	int		size_line;
	int		width;
	int		height;
}				t_xpm;

typedef struct s_sprite
{
	int			alive;
	float		x;
	float		y;
	float		distance;
	int			visible;
	float		angle;
}				t_sprite;

typedef struct s_mlx
{
	int			infoline;
	char		**info;
	void		*mlx;
	void		*win;
	void		*img;
	int			*addr;
	int			bits;
	int			endian;
	int			linelen;
	t_xpm		xpm[8];
	int			frame;

	int			f;
	int			c;
	int			no;
	int			so;
	int			ea;
	int			we;
	char		*floor;
	int			frgb[3];
	int			crgb[3];
	char		*ceiling;
	char		*north;
	char		*south;
	char		*east;
	char		*west;

	t_sprite	*sprite;
	int			count;

	int			tick;
	char		**map;
	int			mapy;
	int			mapx;
	float		looking;
	float		gap;
	float		px;
	float		py;
	float		fov;
	int			cubesize;
	int			proj;
	int			pheight;
	int			life;
	int			god;
	int			advanced;

	float		hdist;
	float		vdist;
	float		*alldist;
	float		horx;
	float		hory;
	float		vertx;
	float		verty;

	int			forward;
	int			right;
	int			left;
	int			backward;
	int			turnright;
	int			turnleft;
	int			end;
	int			lookup;
	int			lookdown;
	int			fight;
	float		sneak;

	char		*bmpheader;
	int			fd;
	int			screenshot;
	int			save;

	long long	last_time;
	float		time;
}				t_mlx;

//cub3d.c

void		raycasting(t_mlx *data);

//init

int			init_struct(t_mlx *data);
void		init_player(t_mlx *data);
int			init_texture(t_mlx *data);
int			init_mlx(t_mlx *data, char *str);

//parsing

int			parsing(t_mlx *data, char *str);

//parsing_utility

char		**get_file_size(t_mlx *data, char *str);
int			check_path(t_mlx *data);
int			verif_player(t_mlx *data);
int			check_color(t_mlx *data, int *rgb, int invalid);

//map_parsing

int			spam_fill(t_mlx *data, char **map, int x, int y);
char		**copy_map(t_mlx *data);
int			check_map(t_mlx *data);
int			get_map_size(t_mlx *data, char **info, int start);
int			get_map(t_mlx *data, char **info);

//error

int			error(t_mlx *data, int nb, int line);

//raycasting

void		get_closest_wall(t_mlx *data, int x, float patch);
void		get_closest_horizontal_wall(t_mlx *data, float ray);
void		get_closest_vertical_wall(t_mlx *data, float ray);
void		get_first_vert(t_mlx *data, float ray);
void		get_first_hor(t_mlx *data, float ray);

//sprite

int			sprite(t_mlx *data);
void		get_sprite_position(t_mlx *data, t_sprite *sprite);
void		sort_sprite(t_mlx *data, t_sprite *sprite, int count);

//get_key

int			keypress(int key, t_mlx *data);
int			keyrelease(int key, t_mlx *data);
void		event(t_mlx *data);

//event

int			moov_player(t_mlx *data);
void		moov_camera(t_mlx *data);
void		action(t_mlx *data, t_sprite *sprite);
int			exit_game(t_mlx *data);

//draw

void		clear_win(t_mlx *data);
void		print_column(t_mlx *data, int x, int height, int texture);
void		sky_box(t_mlx *data);

//screenshot

int			bmp_header(t_mlx *data, char **header);
void		take_screenshot(t_mlx *data);

//utility

float		get_direction(t_mlx *data);
float		*rotate(float *centerxy, float *pointxy, float angle);
int			shading(float dist, unsigned int rgb);
float		get_distance(float x1, float y1, float x2, float y2);
float		angle_range(float angle);

//utility2

void		init_column_draw(t_mlx *data, t_scale *xy, int height, int x);
long long	get_time(void);
void		free_all(t_mlx *data);

//sprite_utility

void		copy_sprite(t_sprite *sprite, int i);
int			sprite_count(t_mlx *data);
void		valid_sprite(t_mlx *data, int *winx, float *angle, int height);
void		set_sprite_pix(t_mlx *data, t_sprite sprite, t_scale xy);
void		moov_sprite(t_mlx *data, t_sprite *sprite);

//hud

void		life(t_mlx *datai, t_sprite *sprite);
void		hand(t_mlx *data);

#endif
