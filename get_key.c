/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:32:59 by agirona           #+#    #+#             */
/*   Updated: 2021/06/10 20:49:33 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event(t_mlx *data)
{
	if (data->forward == 1 || data->right == 1
		|| data->left == 1 || data->backward == 1)
	{
		if (moov_player(data) == 0)
		{
			ft_putstr("Error\nMalloc allocation failed.");
			exit_game(data);
		}
	}
	moov_camera(data);
	action(data, data->sprite);
	if (data->end == 1)
		exit_game(data);
	clear_win(data);
	if (data->advanced >= 1)
		sky_box(data);
	raycasting(data);
	if (sprite(data) == 0)
		data->end = 1;
	if (data->advanced >= 2)
		moov_sprite(data, data->sprite);
	if (data->advanced >= 3)
		life(data, data->sprite);
	if (data->advanced >= 4)
		hand(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	keypress2(int key, t_mlx *data)
{
	ft_putnbr(key);
	if (key == KEY_SPACE)
		data->fight = 1;
	if (key == KEY_SCREENSHOT)
		data->screenshot = 1;
	if (key == KEY_G)
	{
		if (data->god == 0)
			data->god = 1;
		else
			data->god = 0;
	}
	if (key == KEY_PLUS)
	{
		data->advanced++;
		if (data->advanced > 6)
			data->advanced = 0;
	}
}

int	keypress(int key, t_mlx *data)
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
	if (key == KEY_UP)
		data->lookup = 1;
	if (key == KEY_DOWN)
		data->lookdown = 1;
	keypress2(key, data);
	return (1);
}

int	keyrelease(int key, t_mlx *data)
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
		data->lookup = 0;
	if (key == KEY_DOWN)
		data->lookdown = 0;
	return (1);
}
