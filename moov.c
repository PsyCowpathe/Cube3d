/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:24:55 by agirona           #+#    #+#             */
/*   Updated: 2021/06/15 20:40:24 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	moov_player(t_mlx *data)
{
	float	*tmp;
	float	centerxy[2];
	float	pointxy[2];
	float	direction;

	direction = get_direction(data);
	centerxy[0] = data->px;
	centerxy[1] = data->py;
	pointxy[0] = data->px + 0.50;
	pointxy[1] = data->py;
	tmp = rotate(centerxy, pointxy, direction);
	if (tmp == NULL)
		return (0);
	if (ft_ischar("02", data->map[(int)(tmp[1])][(int)(tmp[0])])
		&& is_possible(data, tmp) == 1)
	{
		free(tmp);
		pointxy[0] = data->px + 0.15;
		tmp = rotate(centerxy, pointxy, direction);
		if (tmp == NULL)
			return (0);
		data->px = tmp[0];
		data->py = tmp[1];
	}
	free(tmp);
	return (1);
}

void	reset_view(t_mlx *data)
{
	if (data->lookdown == 0 && data->lookup == 0)
	{
		if (data->sneak < 0)
		{
			data->sneak += 5;
			data->pheight = data->pheight + 5;
		}
		if (data->sneak > 0)
		{
			data->sneak -= 5;
			data->pheight = data->pheight - 5;
		}
	}
}

void	moov_camera(t_mlx *data)
{
	if (data->turnright == 1)
		data->looking -= ROT;
	if (data->turnleft == 1)
		data->looking += ROT;
	data->looking = angle_range(data->looking);
	if (data->lookup == 1 && data->lookdown == 0)
		if (data->sneak < 100)
			data->sneak += 5;
	if (data->lookdown == 1 && data->lookup == 0)
		if (data->sneak > -100)
			data->sneak -= 5;
	data->pheight = (WIN_Y / 2) + data->sneak;
	reset_view(data);
	if (data->looking == 45 || data->looking == 135
		|| data->looking == 225 || data->looking == 315)
		data->looking += 2;
}
