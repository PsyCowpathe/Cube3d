/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:55:10 by agirona           #+#    #+#             */
/*   Updated: 2021/04/19 13:23:13 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_first_hor(t_mlx *data, float rayon)
{
	int		tmp;

	tmp = floor(data->py / data->cubesize);
	if (rayon >= 0 && rayon < 180)
		data->hory = tmp * data->cubesize - 0.001;
	else if (rayon >= 180 && rayon <= 360)
		data->hory = tmp * data->cubesize + data->cubesize;
	data->hory = data->hory / data->cubesize;
	data->horx = data->px + (data->py - data->hory) / tan(rayon * (M_PI / 180));
}

void	get_first_vert(t_mlx *data, float rayon)
{
	int		tmp;

	tmp = floor(data->px / data->cubesize);
	if ((rayon > 0 && rayon <= 90) || (rayon > 270 && rayon <= 360))
		data->vertx = tmp * data->cubesize + data->cubesize;
	else
		data->vertx = tmp * data->cubesize - 0.01;
	data->vertx = data->vertx / data->cubesize;
	data->verty = data->py + (data->px - data->vertx) * tan(rayon * (M_PI / 180));
}

float	get_closest_vertical_wall(t_mlx *data, float rayon)
{
	float	nextx;
	float	nexty;
	float	add;

	nextx = data->vertx;
	nexty = data->verty;
	add = tan(rayon * (M_PI / 180));
	while (nextx >= 0 && nextx <= 18 && nexty >= 0 && nexty <= 6 && data->map[(int)nexty][(int)nextx] == '0')
	{
		if (rayon >= 0 && rayon < 90)
		{
			nextx = nextx + data->cubesize;
			nexty = nexty - add;
		}
		else if (rayon >= 90 && rayon < 180)
		{
			nextx = nextx - data->cubesize;
			nexty = nexty + add;
			nextx = nextx - 0.01;
		}
		else if (rayon >= 180 && rayon < 270)
		{
			nextx = nextx - data->cubesize;
			nexty = nexty + add;
			nextx = nextx - 0.01;
		}
		else if (rayon >= 270 && rayon <= 360)
		{
			nextx = nextx + data->cubesize;
			nexty = nexty - add;
		}
	}
	data->savex1 = nextx;
	data->savey1 = nexty;
	data->vdist = sqrt(pow(nextx - data->px, 2) + pow(nexty - data->py, 2));
	return (data->vdist);
}

float	get_closest_horizontal_wall(t_mlx *data, float rayon)
{
	float	nextx;
	float	nexty;
	float	add;

	nextx = data->horx;
	nexty = data->hory;
	add = data->cubesize / tan(rayon * (M_PI / 180));
	while (nextx >= 0 && nextx <= 18 && nexty >= 0 && nexty <= 6 && data->map[(int)nexty][(int)nextx] == '0')
	{
		if (rayon >= 0 && rayon < 90)
		{
			nexty = nexty - data->cubesize;
			nextx = nextx + add;
			nexty = nexty - 0.01;
		}
		else if (rayon >= 90 && rayon < 180)
		{
			nexty = nexty - data->cubesize;
			nextx = nextx + add;
			nexty = nexty - 0.01;
		}
		else if (rayon >= 180 && rayon < 270)
		{
			nexty = nexty + data->cubesize;
			nextx = nextx - add;
		}
		else if (rayon >= 270 && rayon <= 360)
		{
			nexty = nexty + data->cubesize;
			nextx = nextx - add;
		}
	}
	data->savex = nextx;
	data->savey = nexty;
	data->hdist = sqrt(pow(nextx - data->px, 2) + pow(nexty - data->py, 2));
	return (data->hdist);
}

void	get_closest_wall(t_mlx *data, float rayon, int x, float patch)
{
	float	vdist;
	float	hdist;
	float	distance;
	float	wallheight;

	vdist = get_closest_vertical_wall(data, rayon);
	hdist = get_closest_horizontal_wall(data, rayon);
	if (vdist < hdist)
		distance = vdist * cos(patch * (M_PI / 180));
	else
		distance = hdist * cos(patch * (M_PI / 180));
	wallheight = data->cubesize / distance * data->proj;
	if (vdist < hdist)
		print_column(data, x, wallheight / 10);
	else
		print_column(data, x, wallheight / 10);
}

void	calc_distance(t_mlx *data)
{
	float	rayon;
	int		x;
	float	patch;

	patch = -30;
	rayon = data->pa - (data->fov / 2);
	x = WIN_X - 1;
	while (x >= 0)
	{
		if (rayon < 0)
			rayon = 360 + rayon;
		else if (rayon > 360)
			rayon = 0 + (rayon - 360);
		get_first_hor(data, rayon);
		get_first_vert(data, rayon);
		get_closest_wall(data, rayon, x, patch);
		rayon = rayon + data->between;
		patch += data->between;
		x--;
	}
}
