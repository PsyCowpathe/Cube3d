/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:28:35 by agirona           #+#    #+#             */
/*   Updated: 2021/06/13 13:39:46 by agirona          ###   ########lyon.fr   */
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

void	get_closest_vertical_wall(t_mlx *data, float ray)
{
	float	add;
	float	less;

	less = 0;
	if (ray >= 90 && ray < 270)
		less = 0.0001;
	add = tan(ray * (M_PI / 180));
	while ((data->vertx - less) >= 0 && (data->vertx - less) < data->mapx
		&& data->verty >= 0 && data->verty < data->mapy
		&& ft_ischar("02", data->map[(int)data->verty][(int)(data->vertx - less)]))
	{
		if ((ray >= 0 && ray < 90) || (ray >= 270 && ray <= 360))
		{
			data->vertx = data->vertx + data->cubesize;
			data->verty = data->verty - add;
		}
		else
		{
			data->vertx = data->vertx - data->cubesize;
			data->verty = data->verty + add;
		}
	}
	data->vdist = sqrt(pow(data->vertx - data->px, 2)
		+ pow(data->verty - data->py, 2));
}

void	get_closest_horizontal_wall(t_mlx *data, float ray)
{
	float	add;
	float	less;

	less = 0;
	if (ray >= 0 && ray < 180)
	   less = 0.0001;	
	add = 1 / tan(ray * (M_PI / 180));
	while (data->horx >= 0 && data->horx <= data->mapx
		&& (data->hory - less) >= 0 && (data->hory - less) <= data->mapy
		&& ft_ischar("02", data->map[(int)(data->hory - less)][(int)data->horx]))
	{
		if ((ray >= 0 && ray < 90) || (ray >= 90 && ray < 180))
		{
			data->hory = data->hory - data->cubesize;
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

void	get_closest_wall(t_mlx *data, int x, float ray, float patch)
{
	float	wallheight;
	float	distance;
	int		texture;

	if (data->vdist < data->hdist)
		distance = data->vdist * cos(patch * (M_PI / 180));
	else
		distance = data->hdist * cos(patch * (M_PI / 180));
	wallheight = data->cubesize / distance * data->proj;
	if (ray >= 90 && ray < 270)
		data->vertx -= 0.0001;
	if (ray >= 0 && ray < 180)
		data->hory -= 0.0001;
	if (data->hdist < data->vdist)
	{
		data->alldist[x] = data->hdist;
		if (data->hory >= (int)data->hory + 0.5)
		{
			//ft_putstr("texture 1");
			//dprintf(1, " hdist = %f, vdist = %f ", data->hdist, data->vdist);
			//dprintf(1, " %f ", data->hory);
			//dprintf(1, "%f", data->hory + 0.5);
			texture = 1;
		}
		else
		{
			//ft_putstr("texture 0");
			texture = 0;
		}
	}
	else
	{
		data->alldist[x] = data->vdist;
		if (data->vertx >= (int)data->vertx + 0.5)
		{
			//ft_putstr("texture 2");
			//dprintf(1, " hdist = %f, vdist = %f ", data->hdist, data->vdist);
			//dprintf(1, " %f ", data->hory);
			//dprintf(1, "%f", data->hory + 0.5);
			texture = 2;
		}
		else
		{
			//ft_putstr("texture 3");
			texture = 3;
		}
	}
	ft_putchar('\n');
	print_column(data, x, wallheight, texture);
}
