/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:28:35 by agirona           #+#    #+#             */
/*   Updated: 2021/06/15 16:29:44 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_first_hor(t_mlx *data, float ray)
{
	int		tmp;

	tmp = floor(data->py / data->cubesize);
	if (ray >= 0 && ray < 180)
		data->hory = tmp * data->cubesize;
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
		data->vertx = tmp * data->cubesize;
	data->vertx = data->vertx / data->cubesize;
	data->verty = data->py + (data->px - data->vertx) * tan(ray * (M_PI / 180));
}

void	get_closest_vertical_wall(t_mlx *da, float ray)
{
	float	add;
	float	less;

	less = 0;
	if (ray >= 90 && ray < 270)
		less = 0.0001;
	add = tan(ray * (M_PI / 180));
	while ((da->vertx - less) >= 0 && (da->vertx - less) < da->mapx
		&& da->verty >= 0 && da->verty < da->mapy
		&& ft_ischar("02", da->map[(int)da->verty][(int)(da->vertx - less)]))
	{
		if ((ray >= 0 && ray < 90) || (ray >= 270 && ray <= 360))
		{
			da->vertx = da->vertx + da->cubesize;
			da->verty = da->verty - add;
		}
		else
		{
			da->vertx = da->vertx - da->cubesize;
			da->verty = da->verty + add;
		}
	}
	da->vdist = sqrt(pow(da->vertx - da->px, 2)
			+ pow(da->verty - da->py, 2));
}

void	get_closest_horizontal_wall(t_mlx *da, float ray)
{
	float	add;
	float	less;

	less = 0;
	if (ray >= 0 && ray < 180)
		less = 0.0001;
	add = 1 / tan(ray * (M_PI / 180));
	while (da->horx >= 0 && da->horx < da->mapx
		&& (da->hory - less) >= 0 && (da->hory - less) < da->mapy
		&& ft_ischar("02", da->map[(int)(da->hory - less)][(int)da->horx]))
	{
		if ((ray >= 0 && ray < 90) || (ray >= 90 && ray < 180))
		{
			da->hory = da->hory - da->cubesize;
			da->horx = da->horx + add;
		}
		else
		{
			da->hory = da->hory + da->cubesize;
			da->horx = da->horx - add;
		}
	}
	da->hdist = sqrt(pow(da->horx - da->px, 2)
			+ pow(da->hory - da->py, 2));
}

void	get_closest_wall(t_mlx *data, int x, float ray, float patch)
{
	float	wallheight;
	float	distance;

	if (data->vdist < data->hdist)
		distance = data->vdist * cos(patch * (M_PI / 180));
	else
		distance = data->hdist * cos(patch * (M_PI / 180));
	wallheight = data->cubesize / distance * data->proj;
	if (ray >= 90 && ray < 270)
		data->vertx -= 0.0001;
	if (ray >= 0 && ray < 180)
		data->hory -= 0.0001;
	print_column(data, x, wallheight, choose_text(data, x));
}
