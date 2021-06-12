/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:27:52 by agirona           #+#    #+#             */
/*   Updated: 2021/06/12 21:51:44 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_column_draw(t_mlx *data, t_scale *xy, int height, int x)
{
	xy->len = data->xpm[xy->txt].width;
	if (data->hdist < data->vdist)
		xy->winx = (int)(data->horx * xy->len) % xy->len;
	else
		xy->winx = (int)(data->verty * xy->len) % xy->len;
	xy->winy = data->pheight + (height / 2);
	xy->y = 0;
	xy->x = x;
	if (data->hdist < data->vdist)
		xy->dist = data->hdist;
	else
		xy->dist = data->vdist;
}

void	free_all(t_mlx *data)
{
	int		i;

	i = 0;
	while (i < data->infoline + 1)
	{
		if (data->info[i] != NULL)
			free(data->info[i]);
		i++;
	}
	if (data->info != NULL)
		free(data->info);
	i = 0;
	while (i < data->mapy)
	{
		if (data->map[i] != NULL)
			free(data->map[i]);
		i++;
	}
	if (data->map != NULL)
		free(data->map);
}

int	is_it_possible(t_mlx *data, float *tmp)
{
	float	x;
	float	y;

	x = data->px;
	y = data->py;
	if (x < tmp[0] && y > tmp[1])
	{
		while (x < tmp[0] && y > tmp[1])
		{
			x += 0.1;
			y -= 0.1;
			if (!ft_ischar("02", data->map[(int)y][(int)x]))
				return (0);
		}
	}
	else if (x < tmp[0] && y < tmp[1])
	{
		while (x < tmp[0] && y < tmp[1])
		{
			x += 0.1;
			y += 0.1;
			if (!ft_ischar("02", data->map[(int)y][(int)x]))
				return (0);
		}
	}
	return (1);
}

int	is_possible(t_mlx *data, float *tmp)
{
	float	x;
	float	y;

	x = data->px;
	y = data->py;
	if (x > tmp[0] && y > tmp[1])
	{
		while (x > tmp[0] && y > tmp[1])
		{
			x -= 0.1;
			y -= 0.1;
			if (!ft_ischar("02", data->map[(int)y][(int)x]))
				return (0);
		}
	}
	else if (x > tmp[0] && y < tmp[1])
	{
		while (x > tmp[0] && y < tmp[1])
		{
			x -= 0.1;
			y += 0.1;
			if (!ft_ischar("02", data->map[(int)y][(int)x]))
				return (0);
		}
	}
	else
		return (is_it_possible(data, tmp));
	return (1);
}
