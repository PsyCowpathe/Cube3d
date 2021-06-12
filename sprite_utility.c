/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:10:25 by agirona           #+#    #+#             */
/*   Updated: 2021/06/12 15:33:38 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_sprite(t_sprite *sprite, int i)
{
	t_sprite	tmp[1];

	tmp[0].x = sprite[i].x;
	tmp[0].y = sprite[i].y;
	tmp[0].distance = sprite[i].distance;
	tmp[0].alive = sprite[i].alive;
	sprite[i] = sprite[i + 1];
	sprite[i + 1].x = tmp[0].x;
	sprite[i + 1].y = tmp[0].y;
	sprite[i + 1].distance = tmp[0].distance;
	sprite[i + 1].alive = tmp[0].alive;
}

int	sprite_count(t_mlx *data)
{
	int		count;
	int		x;
	int		y;

	count = 0;
	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	valid_sprite(t_mlx *data, int *winx, float *angle, int height)
{
	if (fabs(data->looking - *angle) > 300)
	{
		if (data->looking > *angle)
			*winx = (WIN_X / 2) - (height / 2)
				+ (((data->looking - 360) - *angle) / data->gap);
		else
			*angle -= 360;
	}
	else
		*winx = (WIN_X / 2) - (height / 2)
			+ ((data->looking - *angle) / data->gap);
}

void	set_sprite_pix(t_mlx *data, t_sprite sprite, t_scale xy)
{
	int		x;
	int		y;

	x = xy.x;
	y = xy.y;
	if (xy.winy >= 0 && xy.winy < WIN_Y && xy.winx >= 0 && xy.winx < WIN_X
		&& data->xpm[xy.txt].addr[y * data->xpm[xy.txt].width + x] >= 0
		&& data->alldist[xy.winx] > sprite.distance)
	{
		if (data->advanced >= 5)
			data->addr[xy.winy * WIN_X + xy.winx] = shading(sprite.distance,
					data->xpm[xy.txt].addr[y
					* data->xpm[xy.txt].width + x]);
		else
			data->addr[xy.winy * WIN_X + xy.winx] = data->xpm[xy.txt].addr[y
				* data->xpm[xy.txt].width + x];
	}
}

void	moov_sprite(t_mlx *d, t_sprite *s)
{
	int		i;
	int		nm;
	int		nl;

	i = -1;
	while (++i < d->count)
	{
		if (s[i].distance < 7 && s[i].distance >= 1.2)
		{
			nm = (s[i].x + 0.1);
			nl = (s[i].x - 0.1);
			if (d->px > s[i].x && ft_ischar("02", d->map[(int)s[i].y][nm]))
				s[i].x += 0.1;
			if (d->px < s[i].x && ft_ischar("02", d->map[(int)s[i].y][nl]))
				s[i].x -= 0.1;
			nm = (s[i].y + 0.1);
			nl = (s[i].y - 0.1);
			if (d->py > s[i].y && ft_ischar("02", d->map[nm][(int)s[i].x]))
				s[i].y += 0.1;
			if (d->py < s[i].y && ft_ischar("02", d->map[nl][(int)s[i].x]))
				s[i].y -= 0.1;
		}
	}
}
