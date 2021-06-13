/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:07:32 by agirona           #+#    #+#             */
/*   Updated: 2021/06/13 13:39:43 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_clear_pix(t_mlx *data, t_scale *xy, float vgap)
{
	int		color;

	color = create_trgb(0, data->frgb[0], data->frgb[1], data->frgb[2]);
	xy->y -= 1;
	if (data->advanced >= 5)
	{
		if (xy->x < (WIN_X / 2))
			data->addr[(int)xy->y * WIN_X + (int)xy->x] = shading(
					(xy->vdist * 0.5) + xy->hdist, color);
		else
			data->addr[(int)xy->y * WIN_X + (int)xy->x] = shading(
					xy->hdist - (xy->vdist * 0.5), color);
	}
	else
		data->addr[(int)xy->y * WIN_X + (int)xy->x] = color;
	xy->vdist -= vgap;
	xy->y += 1;
}

void	clear_win(t_mlx *data)
{
	t_scale	xy;
	float	hgap;
	float	vgap;
	float	save;

	xy.y = -1;
	xy.hdist = get_distance(WIN_X / 2, WIN_Y, 0, 0) / 100;
	hgap = (float)xy.hdist / (data->pheight - (data->sneak * 2));
	xy.vdist = get_distance(WIN_X / 2, WIN_Y / 2, 0, 0) / 100;
	vgap = (float)xy.vdist / (WIN_X / 2);
	save = xy.vdist;
	while (++xy.y < data->pheight)
	{
		xy.x = -1;
		while (++xy.x < WIN_X)
			data->addr[(int)xy.y * WIN_X + (int)xy.x] = create_trgb(0, data->crgb[0], data->crgb[1], data->crgb[2]);
	}
	while (xy.y++ < WIN_Y)
	{
		xy.x = -1;
		while (++xy.x < WIN_X)
			set_clear_pix(data, &xy, vgap);
		xy.vdist = save;
		xy.hdist -= hgap;
	}
}

void	sky_box(t_mlx *data)
{
	int		x;
	int		y;
	float	skyx;
	float	skyy;

	x = WIN_X;
	skyx = 0 + (float)((data->xpm[5].width
				/ (float)360) * data->looking) + data->time;
	while (x > 0)
	{
		y = 0;
		skyy = 0;
		while (y < data->pheight)
		{
			data->addr[y * WIN_X + x] = data->xpm[5].addr[(int)skyy
				* data->xpm[5].width + (int)skyx];
			y++;
			skyy += (float)data->xpm[5].height / WIN_Y;
		}
		x--;
		skyx += (float)data->xpm[5].width / (float)(WIN_X * 6);
	}
}

void	print_column(t_mlx *data, int x, int height, int texture)
{
	float	i;
	float	gap;
	t_scale	xy;

	i = 0;
	xy.txt = texture;
	gap = (float)data->xpm[xy.txt].height / height;
	init_column_draw(data, &xy, height, x);
	while (i < height)
	{
		if (xy.winy - i >= 0 && xy.winy - i < WIN_Y && xy.x >= 0 && xy.x < WIN_X
			&& (int)xy.y >= 0 && (int)xy.y < data->xpm[xy.txt].height
			&& xy.winx >= 0 && xy.winx < xy.len)
		{
			if (data->advanced >= 5)
				data->addr[(xy.winy - (int)i) *WIN_X + (int)xy.x] = shading(
						xy.dist, data->xpm[xy.txt].addr[(int)xy.y
						* xy.len + xy.winx]);
			else
				data->addr[(xy.winy - (int)i) *WIN_X + (int)xy.x] = data->xpm[
					xy.txt].addr[(int)xy.y * xy.len + xy.winx];
		}
		i++;
		xy.y += gap;
	}
}
