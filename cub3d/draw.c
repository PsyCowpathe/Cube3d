/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:53:37 by agirona           #+#    #+#             */
/*   Updated: 2021/04/19 11:04:56 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel(t_mlx *data, int x, int y, int color)
{
	if (x >= 0 && x < WIN_X && y >= 0 && y < WIN_Y)
		data->addr[y * WIN_X + x] = color;
}

void	print_column(t_mlx *data, int x, int height)
{
	float	i;
	float	between;
	float	y;
	int		tmpx;
	int		tmpy;

	i = 0;
	between = (float)64 / ((height * 4));
	if (data->hdist < data->vdist)
		tmpx = (int)(data->savex * 64) % 64;
	else
		tmpx = (int)(data->savey1 * 64) % 64;
	tmpy = (WIN_Y / 2) + ((height * 4) / 2);
	y = 0;
	while (i < height * 4)
	{
		if ((tmpy - (int)i) * WIN_X + x > 0 && (tmpy - (int)i) * WIN_X + x < WIN_X * WIN_Y)
		{
			if ((int)y * 64 + tmpx >= 0 && (int)y * 64 + tmpx <= 64 * 64)
			data->addr[(tmpy - (int)i) * WIN_X + x] = data->text_data[(int)y * 64 + tmpx];
		}
		i++;
		y += between;
	}
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
			if (y <= (WIN_Y / 2))
				set_pixel(data, x, y, SKY);
			else
				set_pixel(data, x, y, DIRT);
			x++;
		}
		x = 0;
		y++;
	}
}
