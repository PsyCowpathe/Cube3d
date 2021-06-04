/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:32:59 by agirona           #+#    #+#             */
/*   Updated: 2021/05/13 15:08:31 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event(t_mlx *data)
{
	if (data->forward == 1 || data->right == 1
	|| data->left == 1 || data->backward == 1)
		moov_player(data);
	if (data->turnright == 1 || data->turnleft == 1)
		moov_camera(data);
	if (data->end == 1)
		exit_game(data);
	clear_win(data);
	get_distance(data);
	sprite(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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
	if (key == KEY_ECHAP)
		data->end = 1;
	//event(data);
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
	//event(data);
	return (1);
}
