/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:32:59 by agirona           #+#    #+#             */
/*   Updated: 2021/06/15 17:25:13 by agirona          ###   ########lyon.fr   */
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
		free(data->bmpheader);
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

int	exit_game(t_mlx *data)
{
	free_all(data);
	system("killall afplay");
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
	return (1);
}
