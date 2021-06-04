/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:36:55 by agirona           #+#    #+#             */
/*   Updated: 2021/05/19 17:43:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		sprite_count(t_mlx *data)
{
	int		count;
	int		x;
	int		y;

	count = 0;
	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x <= 43)
		{
			if (data->map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

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
		while (x <= 43)
		{
			if (data->map[y][x] == '2')
			{
				sprite[i].visible = 0;
				sprite[i].x = x + 0.5;
				sprite[i].y = y + 0.5;
				sprite[i].distance = sqrt(pow(x - data->px, 2) + pow(y - data->py, 2));//optimisation possible
				//si placer dans le sort_sprite
				i++;
			}
			x++;
		}
		y++;
	}
}

void	sort_sprite(t_sprite *sprite, int count)
{
	t_sprite	tmp[1];
	int			i;

	i = 0;
	while (i < count - 1 && count > 1)
	{
		if (sprite[i].distance < sprite[i + 1].distance)
		{
			tmp[0].x = sprite[i].x;
			tmp[0].y = sprite[i].y;
			tmp[0].distance = sprite[i].distance;
			sprite[i] = sprite[i + 1];
			sprite[i + 1].x = tmp[0].x;
			sprite[i + 1].y = tmp[0].y;
			sprite[i + 1].distance = tmp[0].distance;
			i = 0;
		}
		else
			i++;
	}
}

float	get_angle(float *origin, float *decalage, float *arrive)
{
	float	angle;
	float	dp;
	float	da;
	float	ao;
	
	dp = sqrt(pow(decalage[0] - origin[0], 2) + pow(decalage[1] - origin[1], 2));
	da = sqrt(pow(decalage[0] - arrive[0], 2) + pow(decalage[1] - arrive[1], 2));
	ao = sqrt(pow(arrive[0] - origin[0], 2) + pow(arrive[1] - origin[1], 2));
	angle = pow(ao, 2) + pow(dp, 2) - pow(da, 2);
	angle = angle / (2 * ao * dp);
	angle = acosf(angle) * 180 / M_PI;
	return (angle);
}

void	get_visible_sprite(t_mlx *data, t_sprite *sprite, int count)
{
	int		i;
	float	angle;
	float	max;
	float	min;
	i = 0;
	max = data->looking + 40;
	min = data->looking - 40;
	if (max > 360)
		max = 0 + (max - 360);
	if (min < 0)
		min = 360 + min;
	while (i < count)
	{
		angle = atan2(sprite[i].y - data->py, sprite[i].x - data->px);
		angle = angle * 180 / M_PI;
		angle = fmod(angle - 360, 360) * -1;
		if (min > max)
		{
			if ((angle >= 0 && angle <= max) || (angle >= min && angle <= 360))
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
	int		height;
	float	y;
	float	x;
	int		winx;
	int		winy;

	height = data->cubesize / sprite.distance * data->proj;
	winy = data->pheight - (height / 2);
	//dprintf(1, "x = %f ", (WIN_X / 2) + ((data->looking - sprite.angle) / data->gap));
	//dprintf(1, " Visible = %d Looking = %f, Sprite = %f, Gap = %f\n",
	//sprite.visible, data->looking, sprite.angle, data->gap);
	y = 0;
	while (y < data->xpm[4].img_height)
	{
		x = 0;
		if (sprite.angle > 300)
			sprite.angle = sprite.angle - 360;
		if (data->looking > 300)
			winx = (WIN_X / 2) + (((data->looking - 360) - sprite.angle) / data->gap);
		else
			winx = (WIN_X / 2) + ((data->looking - sprite.angle) / data->gap);
		while (x < data->xpm[4].img_width)
		{
			if (winy >= 0 && winy < WIN_Y && winx >= 0 && winx < WIN_X
			&& data->xpm[4].addr[(int)y * data->xpm[4].img_width + (int)x] >= 0 && data->alldist[winx] > sprite.distance)
				data->addr[winy * WIN_X + winx] = data->xpm[4].addr[(int)y * data->xpm[4].img_width + (int)x];
			x = x + (float)data->xpm[4].img_width / height;
			winx++;
		}
		y = y + (float)data->xpm[4].img_height / height;
		winy++;
	}
}

int		sprite(t_mlx *data)
{
	int			count;
	t_sprite	*sprite;
	int			i;

	i = 0;
	count = sprite_count(data);
	sprite = malloc(sizeof(t_sprite) * count);
	if (sprite == NULL)
		return (0);
	get_sprite_position(data, sprite);
	sort_sprite(sprite, count);
	get_visible_sprite(data, sprite, count);
	while (i < count)
	{
		if (sprite[i].visible == 1)
			draw_sprite(data, sprite[i]);
		i++;
	}
	return (1);
}
