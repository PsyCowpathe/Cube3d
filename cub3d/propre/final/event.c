/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:32:59 by agirona           #+#    #+#             */
/*   Updated: 2021/05/14 14:49:09 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_direction(t_mlx *data)
{
	float	direction;

	direction = 0;
	if (data->forward == 1)
	 	direction = data->looking;
	if (data->backward == 1)
		direction = data->looking - 180;
	if (data->right == 1)
		direction = data->looking - 90;
	if (data->left == 1)
		direction = data->looking + 90;
	return (direction * (M_PI / 180));
}

void	moov_player(t_mlx *data)
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
	if (data->map[(int)(tmp[1])][(int)(tmp[0])] == '0' || data->map[(int)(tmp[1])][(int)(tmp[0])] == '2')
	{
		pointxy[0] = data->px + 0.15;
		tmp = rotate(centerxy, pointxy, direction); 
		data->px = tmp[0];
		data->py = tmp[1];
	}
}

void	moov_camera(t_mlx *data)
{
	if (data->turnright == 1)
	{
		data->looking -= ROT;
		if (data->looking < 0)
			data->looking = 360 + data->looking;
	}
	if (data->turnleft == 1)
	{
		data->looking += ROT;
		if (data->looking > 360)
			data->looking = 0 + (data->looking - 360);
	}
}

void	exit_game(t_mlx *data)
{
	int		i;

	i = 0;
	while (i < 5)
		mlx_destroy_image(data->mlx, data->xpm[i++].img);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
}
