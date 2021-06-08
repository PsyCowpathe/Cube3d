/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:28:35 by agirona           #+#    #+#             */
/*   Updated: 2021/06/08 14:10:30 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_first_hor(t_mlx *data, float ray)
{
	int		tmp;

	tmp = floor(data->py / data->cubesize);
	if (ray >= 0 && ray < 180)
		data->hory = tmp * data->cubesize - 0.000001;
	else if (ray >= 180 && ray <= 360)
		data->hory = tmp * data->cubesize + data->cubesize;
	data->hory = data->hory / data->cubesize;
	data->horx = data->px + (data->py - data->hory) / tan(ray * (M_PI / 180));
}

void	get_first_vert(t_mlx *data, float ray)
{
	int		tmp;

	tmp = floor(data->px / data->cubesize);
	if ((ray > 0 && ray <= 90) || (ray > 270 && ray <= 360))
		data->vertx = tmp * data->cubesize + data->cubesize;
	else
		data->vertx = tmp * data->cubesize - 0.000001;
	data->vertx = data->vertx / data->cubesize;
	data->verty = data->py + (data->px - data->vertx) * tan(ray * (M_PI / 180));
}

void	get_closest_vertical_wall(t_mlx *data, float ray)
{
	float	add;

	add = tan(ray * (M_PI / 180));
	while (data->vertx >= 0 && data->verty < data->mapx
		&& data->verty >= 0 && data->verty < data->mapy
		&& ft_ischar("02", data->map[(int)data->verty][(int)data->vertx]))
	{
		if ((ray >= 0 && ray < 90) || (ray >= 270 && ray <= 360))
		{
			data->vertx = data->vertx + data->cubesize;
			data->verty = data->verty - add;
		}
		else
		{
			data->vertx = data->vertx - data->cubesize - 0.000001;
			data->verty = data->verty + add;
		}
	}
	data->vdist = sqrt(pow(data->vertx - data->px, 2)
			+ pow(data->verty - data->py, 2));
}

void	get_closest_horizontal_wall(t_mlx *data, float ray)
{
	float	add;

	add = 1 / tan(ray * (M_PI / 180));
	while (data->horx >= 0 && data->horx <= data->mapx
		&& data->hory >= 0 && data->hory <= data->mapy
		&& ft_ischar("02", data->map[(int)data->hory][(int)data->horx]))
	{
		if ((ray >= 0 && ray < 90) || (ray >= 90 && ray < 180))
		{
			data->hory = data->hory - data->cubesize - 0.000001;
			data->horx = data->horx + add;
		}
		else
		{
			data->hory = data->hory + data->cubesize;
			data->horx = data->horx - add;
		}
	}
	data->hdist = sqrt(pow(data->horx - data->px, 2)
			+ pow(data->hory - data->py, 2));
}

void	get_closest_wall(t_mlx *data, int x, float patch)
{
	float	wallheight;
	float	distance;
	int		texture;

	if (data->vdist < data->hdist)
		distance = data->vdist * cos(patch * (M_PI / 180));
	else
		distance = data->hdist * cos(patch * (M_PI / 180));
	wallheight = data->cubesize / distance * data->proj;
	if (data->hdist <= data->vdist)
	{
		data->alldist[x] = data->hdist;
		texture = 0;
		if (data->hory >= (int)data->hory + 0.5)
			texture = 1;
	}
	else
	{
		data->alldist[x] = data->vdist;
		texture = 3;
		if (data->vertx >= (int)data->vertx + 0.5)
			texture = 2;
	}
	print_column(data, x, wallheight, texture);
}
