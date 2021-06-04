/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:27:52 by agirona           #+#    #+#             */
/*   Updated: 2021/05/23 21:08:17 by agirona          ###   ########lyon.fr   */
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
