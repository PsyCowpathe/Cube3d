/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:43:32 by agirona           #+#    #+#             */
/*   Updated: 2021/05/14 15:21:40 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		event(t_mlx *data)
{
	float	*tmp;
	float	centerxy[2];
	float	pointxy[2];

	if (data->forward == 1)
	{
		centerxy[0] = data->px;
		centerxy[1] = data->py;
		pointxy[0] = data->px + 0.1;
		pointxy[1] = data->py;
		tmp = rotate(centerxy, pointxy, data->looking * (M_PI / 180));
		if (data->map[(int)tmp[1]][(int)tmp[0]] == '0')
		{
			data->px = tmp[0];
			data->py = tmp[1];
		}
	}
	if (data->right == 1)
	{
		centerxy[0] = data->px;
		centerxy[1] = data->py;
		pointxy[0] = data->px + 0.05;
		pointxy[1] = data->py;
		tmp = rotate(centerxy, pointxy, (data->looking - 90) * (M_PI / 180));
		if (data->map[(int)tmp[1]][(int)tmp[0] + 1] == '0')
		{
			data->px = tmp[0];
			data->py = tmp[1];
		}
	}
	if (data->left == 1)
	{
		centerxy[0] = data->px;
		centerxy[1] = data->py;
		pointxy[0] = data->px + 0.05;
		pointxy[1] = data->py;
		tmp = rotate(centerxy, pointxy, (data->looking + 90) * (M_PI / 180));
		if (data->map[(int)tmp[1]][(int)tmp[0]] == '0') //add limit protection
		{
			data->px = tmp[0];
			data->py = tmp[1];
		}
		data->px = tmp[0];
		data->py = tmp[1];
	}
	if (data->backward == 1)
	{
		centerxy[0] = data->px;
		centerxy[1] = data->py;
		pointxy[0] = data->px + 0.03;
		pointxy[1] = data->py;
		tmp = rotate(centerxy, pointxy, (data->looking - 180) * (M_PI / 180));
		if (data->map[(int)tmp[1]][(int)tmp[0]] == '0')
		{
			data->px = tmp[0];
			data->py = tmp[1];
		}
	}
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
	if (data->lookup == 1 && data->lookdown == 0)
		data->pheight = (WIN_Y / 2) + data->sneak;
	if (data->lookdown == 1 && data->lookup == 0)
		data->pheight = (WIN_Y / 2) - 100;
	if (data->lookup == 0 && data->lookdown == 0)
		data->pheight = (WIN_Y / 2);
	//clear_win(data);
	//sky_box(data);
	//get_distance(data);
	//mini_map(data, 20);
	//texture(data);
	//mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (1);
}

void	exit_game(t_mlx *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
}

int		keypress(int key, t_mlx *data)
{
	if (key == KEY_W)
		data->forward = 1;
	if (key == KEY_D)
		data->right = 1;
	if (key == KEY_A)
		data->left = 1;
	if (key == KEY_S)
		data->backward = 1;
	if (key == KEY_LEFT_TURN)
		data->turnleft = 1;
	if (key == KEY_RIGHT_TURN)
		data->turnright = 1;
	if (key == KEY_UP)
		data->lookup = 1;
	if (key == KEY_DOWN)
		data->lookdown = 1;
	if (key == KEY_ECHAP)
		data->end = 1;
	return (1);
}

int		keyrelease(int key, t_mlx *data)
{
	if (key == KEY_W)
		data->forward = 0;
	if (key == KEY_D)
		data->right = 0;
	if (key == KEY_A)
		data->left = 0;
	if (key == KEY_S)
		data->backward = 0;
	if (key == KEY_LEFT_TURN)
		data->turnleft = 0;
	if (key == KEY_RIGHT_TURN)
		data->turnright = 0;
	if (key == KEY_UP)
	{
		data->sneak = 0;
		data->lookup = 0;
	}
	if (key == KEY_DOWN)
		data->lookdown = 0;
	return (1);
}
