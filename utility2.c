/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:27:52 by agirona           #+#    #+#             */
/*   Updated: 2021/06/10 20:49:31 by agirona          ###   ########lyon.fr   */
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
