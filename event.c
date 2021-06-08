/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:32:59 by agirona           #+#    #+#             */
/*   Updated: 2021/06/08 18:10:28 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	secondary_action(t_mlx *data)
{
	if (data->fight == 1 || data->fight == 2)
	{
		if (data->frame > 90)
		{
			data->fight = 0;
			data->frame = 1;
		}
		else
			data->frame += 5;
	}
	if (data->screenshot == 1)
	{
		data->screenshot = 0;
		bmp_header(data, &data->bmpheader);
		take_screenshot(data);
	}
}

void	action(t_mlx *data, t_sprite *sprite)
{
	int		i;

	i = 0;
	while (i < data->count)
	{
		if (data->fight == 1 && sprite[i].distance <= 1.5
			&& sprite[i].visible == 1 && data->frame >= 20
			&& data->frame <= 30 && sprite[i].alive == 1)
		{
			system("afplay ../../../sound/sprite-hurt.wav -v 0.5 &");
			data->life += 10;
			if (data->life > 100)
				data->life = 100;
			data->fight = 2;
			sprite[i].alive = 0;
		}
		i++;
	}
	secondary_action(data);
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
	if (ft_ischar("02", data->map[(int)(tmp[1])][(int)(tmp[0])]))
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

void	free_all(t_mlx *data)
{
	int		i;

	i = 0;
	while (i < 8)
		mlx_destroy_image(data->mlx, data->xpm[i++].img);
	i = 0;
	while (i < data->mapy)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

int	exit_game(t_mlx *data)
{
	char	*mall;

	mall = malloc(sizeof(char) * 5);
	free_all(data);
	system("killall afplay");
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	while (1);
	exit(EXIT_SUCCESS);
	return (1);
}
