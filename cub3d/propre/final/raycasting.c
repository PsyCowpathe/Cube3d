/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:28:35 by agirona           #+#    #+#             */
/*   Updated: 2021/05/24 21:04:14 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_first_hor(t_mlx *data, float ray)
{
	int		tmp;

	tmp = floor(data->py / data->cubesize);
	if (ray >= 0 && ray < 180)
		data->hory = tmp * data->cubesize - 0.00001;
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
		data->vertx = tmp * data->cubesize - 0.00001;
	data->vertx = data->vertx / data->cubesize;
	data->verty = data->py + (data->px - data->vertx) * tan(ray * (M_PI / 180));
}

float	get_closest_vertical_wall(t_mlx *data, float ray)
{
	float	nextx;
	float	nexty;
	float	add;

	nextx = data->vertx;
	nexty = data->verty;
	add = tan(ray * (M_PI / 180));
	while (nextx >= 0 && nextx <= 43 && nexty >= 0 && nexty <= 14
	&& (data->map[(int)nexty][(int)nextx] == '0' || data->map[(int)nexty][(int)nextx] == '2'))
	{
		if (ray >= 0 && ray < 90)
		{
			nextx = nextx + data->cubesize;
			nexty = nexty - add;
		}
		else if (ray >= 90 && ray < 180)
		{
			nextx = nextx - data->cubesize;
			nexty = nexty + add;
			nextx = nextx - 0.00001;
		}
		else if (ray >= 180 && ray < 270)
		{
			nextx = nextx - data->cubesize;
			nexty = nexty + add;
			nextx = nextx - 0.00001;
		}
		else if (ray >= 270 && ray <= 360)
		{
			nextx = nextx + data->cubesize;
			nexty = nexty - add;
		}
	}
	data->vertx = nextx;
	data->verty = nexty;
	data->vdist = sqrt(pow(nextx - data->px, 2) + pow(nexty - data->py, 2));
	return (data->vdist);
}

float	get_closest_horizontal_wall(t_mlx *data, float ray)
{
	float	nextx;
	float	nexty;
	float	add;

	nextx = data->horx;
	nexty = data->hory;
	add = data->cubesize / tan(ray * (M_PI / 180));
	while (nextx >= 0 && nextx <= 43 && nexty >= 0 && nexty <= 14
	&& (data->map[(int)nexty][(int)nextx] == '0' || data->map[(int)nexty][(int)nextx] == '2'))
	{
		if (ray >= 0 && ray < 90)
		{
			nexty = nexty - data->cubesize;
			nextx = nextx + add;
			nexty = nexty - 0.00001;
		}
		else if (ray >= 90 && ray < 180)
		{
			nexty = nexty - data->cubesize;
			nextx = nextx + add;
			nexty = nexty - 0.00001;
		}
		else if (ray >= 180 && ray < 270)
		{
			nexty = nexty + data->cubesize;
			nextx = nextx - add;
		}
		else if (ray >= 270 && ray <= 360)
		{
			nexty = nexty + data->cubesize;
			nextx = nextx - add;
		}
	}
	data->horx = nextx;
	data->hory = nexty;
	data->hdist = sqrt(pow(nextx - data->px, 2) + pow(nexty - data->py, 2));
	return (data->hdist);
}

void	get_closest_wall(t_mlx *data, float ray, int x, float patch)
{
	float	wallheight;
	float	distance;
	int		texture;

	data->vdist = get_closest_vertical_wall(data, ray);
	data->hdist = get_closest_horizontal_wall(data, ray);
	if (data->vdist < data->hdist)
		distance = data->vdist * cos(patch * (M_PI / 180));
	else
		distance = data->hdist * cos(patch * (M_PI / 180));
	wallheight = data->cubesize / distance * data->proj;
	if (data->hdist <= data->vdist)
	{
		data->alldist[x] = data->hdist;
		if (data->hory >= (int)data->hory + 0.5)
			texture = 1;
		else
			texture = 0;
	}
	else
	{
		data->alldist[x] = data->vdist;
		if (data->vertx >= (int)data->vertx + 0.5)
			texture = 2;
		else
			texture = 3;
	}
	print_column(data, x, wallheight, texture);
}

void	get_distance(t_mlx *data)
{
	int		x;
	float	ray;
	float	patch;

	x = WIN_X - 1;
	ray = data->looking - (data->fov / 2);
	patch = (data->fov / 2) * -1;
	while (x >= 0)
	{
		if (ray < 0)
			ray = 360 + ray;
		else if (ray > 360)
			ray = 0 + (ray - 360);
		get_first_hor(data, ray);
		get_first_vert(data, ray);
		get_closest_wall(data, ray, x, patch);
		patch = patch + data->gap; //leger fisheyes ?
		ray = ray + data->gap;
		x--;
	}
}
