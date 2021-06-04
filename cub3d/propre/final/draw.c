/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:07:32 by agirona           #+#    #+#             */
/*   Updated: 2021/05/09 16:43:25 by agirona          ###   ########lyon.fr   */
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

	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			if (y <= data->pheight)
				set_pixel(data, x, y, 0xFF00FF);
			else
				set_pixel(data, x, y, DIRT);
			x++;
		}
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
