/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:57:10 by agirona           #+#    #+#             */
/*   Updated: 2021/05/23 21:08:16 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_frame(t_mlx *data, int *save, int *max)
{
	if (data->frame <= 10)
	{
		*max = data->xpm[6].width;
		*save = 465;
	}
	else if (data->frame <= 20)
	{
		*max = data->xpm[6].width - (data->xpm[6].width - 465);
		*save = 245;
	}
	else if (data->frame <= 30)
	{
		*max = data->xpm[6].width - (data->xpm[6].width - 245);
		*save = 102;
	}
	else if (data->frame <= 40)
	{
		*max = data->xpm[6].width - (data->xpm[6].width - 102);
		*save = 0;
	}
}

void	hand(t_mlx *data)
{
	t_scale	xy;
	int		max;
	int		save;

	xy.y = 0;
	xy.winy = WIN_Y - data->xpm[6].height;
	select_frame(data, &save, &max);
	while (xy.y < data->xpm[6].height)
	{
		xy.x = save;
		xy.winx = WIN_X / 2 + (xy.x / 2);
		while (xy.x < max && data->frame <= 40)
		{
			if (data->xpm[6].addr[(int)xy.y
					* data->xpm[6].width + (int)xy.x] >= 0
				&& xy.y >= 0 && xy.y < data->xpm[6].height
				&& xy.x >= 0 && xy.x < data->xpm[6].width)
				data->addr[xy.winy * WIN_X + xy.winx] = data->xpm[6].addr[
					(int)xy.y * data->xpm[6].width + (int)xy.x];
			xy.winx++;
			xy.x++;
		}
		xy.winy++;
		xy.y++;
	}
}

void	draw_life(t_mlx *data)
{
	int		x;
	int		y;
	float	xmax;

	y = WIN_Y - 50;
	x = 50;
	while (x < 500)
		data->addr[y * WIN_X + x++] = 0x000000;
	while (y < WIN_Y - 30)
		data->addr[y++ *WIN_X + x] = 0x000000;
	while (x > 50)
		data->addr[y * WIN_X + x--] = 0x000000;
	while (y > WIN_Y - 50)
		data->addr[y-- *WIN_X + x] = 0x000000;
	xmax = (float)450 / 100;
	xmax *= data->life;
	xmax += 50;
	while (++y < WIN_Y - 30)
	{
		x = 50;
		while (++x < xmax)
			data->addr[y * WIN_X + x] = 0xFF0000;
	}
}

void	life(t_mlx *data, t_sprite *sprite)
{
	int		i;

	i = 0;
	while (i < data->count)
	{
		if (data->god == 0 && sprite[i].distance <= 1.2 && sprite[i].alive == 1)
			data->life -= 2;
		i++;
	}
	if (data->life <= 0)
		data->end = 1;
	draw_life(data);
}
