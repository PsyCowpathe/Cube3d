/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:56:39 by agirona           #+#    #+#             */
/*   Updated: 2021/05/15 12:29:44 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel(t_mlx *data, int x, int y, int color)
{
	if (x >= 0 && x < WIN_X && y >= 0 && y < WIN_Y)
		data->addr[y * WIN_X + x] = color;
}

void	clear_win(t_mlx *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < WIN_Y)
	{
		while (x < WIN_X)
		{
			if (y <= data->pheight)
				set_pixel(data, x, y, 0xFF00FF);
			else
				set_pixel(data, x, y, DIRT);
			x++;
		}
		x = 0;
		y++;
	}
}

void	sky_box(t_mlx *data)
{
	int		x;
	int		y;
	float	skyx;
	float	skyy;
	
	y = 0;
	skyy = 0 + data->time;
	while (y <= data->pheight)
	{
		x = 0;
		skyx = (float)11520 - (data->looking) * (float)((WIN_X * 6) / 360);
		while (x < WIN_X)
		{
			if (skyx > 11520)
				skyx = 0;
			if (skyy >= 0 && skyy <= 2160 && skyx >= 0 && skyx <= 11520)
				data->addr[y * WIN_X + x] = data->xpm[5].addr[(int)(skyy * 11520 + skyx)];
			skyx += (float)11520 / (WIN_X * 12);
			x++;
		}
		skyy += (float)2160 / WIN_Y;
		y++;
	}
}

void	print_column(t_mlx *data, int x, int height, int texture)
{
	float	i;
	float	gap;
	float	y;
	int		tmpx;
	int		tmpy;
	int		len;

	len = data->xpm[texture].img_width;
	i = 0;
	gap = (float)data->xpm[texture].img_height / height;
	if (data->hdist < data->vdist)
		tmpx = (int)(data->horx * len) % len;
	else
		tmpx = (int)(data->verty * len) % len;
	tmpy = data->pheight + (height / 2);
	y = 0;
	while (i < height)
	{
		if (tmpy - (int)i >= 0 && tmpy - (int)i < WIN_Y && x >= 0 && x < WIN_X
		&& (int)y >= 0 && (int)y < data->xpm[texture].img_height && tmpx >= 0 && tmpx < len)
			data->addr[(tmpy - (int)i) * WIN_X + x] = data->xpm[texture].addr[(int)y * len + tmpx];
		i++;
		y += gap;
	}
}

void	sprite(t_mlx *data, int x, float dist)
{
	float	tmpx;
	float	tmpy;
	int		height;
	int		winy;
	int		save;
	int		i;

	x = data->lastx + ((data->firstx - data->lastx) / 2);
	save = x;
	dist = sqrt(pow(data->spritex - data->px, 2) + pow(data->spritey - data->py, 2));
	height = data->cubesize / dist * data->proj;
	winy = data->pheight + (height / 2);
	tmpy = 750;
	i = 0;
	while (i < height)
	{
		tmpx = 750;
		while (tmpx > 0)
		{
			if (tmpy >= 0 && tmpy < 750 && tmpx >= 0 && tmpx < 750 && data->xpm[4].addr[(int)tmpy * 750 + (int)tmpx] >= 0
			&& winy * WIN_X + x >= 0 && winy * WIN_X + x < WIN_X * WIN_Y)
				data->addr[winy * WIN_X + x] = data->xpm[4].addr[(int)tmpy * 750 + (int)tmpx];
			tmpx = tmpx - (float)750 / height;
			x++;
		}
		i++;
		x = save;
		winy--;
		tmpy = tmpy - (float)750 / height;
	}
}
