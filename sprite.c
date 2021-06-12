/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:36:55 by agirona           #+#    #+#             */
/*   Updated: 2021/06/12 15:33:37 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sprite_position(t_mlx *data, t_sprite *sprite)
{
	int		x;
	int		y;
	int		i;

	y = 0;
	i = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] == '2')
			{
				sprite[i].alive = 1;
				sprite[i].visible = 0;
				sprite[i].x = x + 0.5;
				sprite[i].y = y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	sort_sprite(t_mlx *data, t_sprite *spr, int count)
{
	int			i;

	i = -1;
	while (++i < count)
		spr[i].distance = get_distance(spr[i].x, spr[i].y, data->px, data->py);
	i = 0;
	while (i < count - 1)
	{
		if (spr[i].distance < spr[i + 1].distance)
		{
			copy_sprite(spr, i);
			i = 0;
		}
		else
			i++;
	}
}

void	get_visible_sprite(t_mlx *data, t_sprite *sprite, int count)
{
	int		i;
	float	angle;
	float	max;
	float	min;

	i = 0;
	min = angle_range(data->looking - 60);
	max = angle_range(data->looking + 60);
	while (i < count)
	{
		angle = atan2f(sprite[i].y - data->py, sprite[i].x - data->px);
		angle = angle * 180 / M_PI;
		angle = fmod(angle - 360, 360) * -1;
		if (min > max)
		{
			if ((angle >= min && angle <= 360) || (angle >= 0 && angle <= max))
				sprite[i].visible = 1;
		}
		else if (angle >= min && angle <= max)
			sprite[i].visible = 1;
		sprite[i].angle = angle;
		i++;
	}
}

void	draw_sprite(t_mlx *data, t_sprite sprite)
{
	t_scale	xy;
	int		height;

	if (data->tick <= 15 && sprite.distance < 7 && data->advanced >= 6)
		xy.txt = 7;
	else
		xy.txt = 4;
	height = data->cubesize / sprite.distance * data->proj;
	xy.winy = data->pheight - (height / 2);
	xy.y = 0;
	while (xy.y < data->xpm[xy.txt].height)
	{
		xy.x = 0;
		valid_sprite(data, &xy.winx, &sprite.angle, height);
		while (xy.x < data->xpm[xy.txt].width)
		{
			set_sprite_pix(data, sprite, xy);
			xy.x = xy.x + (float)data->xpm[xy.txt].width / height;
			xy.winx++;
		}
		xy.y = xy.y + (float)data->xpm[xy.txt].height / height;
		xy.winy++;
	}
}

int	sprite(t_mlx *data)
{
	int			i;

	i = 0;
	sort_sprite(data, data->sprite, data->count);
	get_visible_sprite(data, data->sprite, data->count);
	while (i < data->count)
	{
		if (data->sprite[i].visible == 1 && data->sprite[i].alive == 1)
			draw_sprite(data, data->sprite[i]);
		i++;
	}
	return (1);
}
