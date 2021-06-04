/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:08:02 by agirona           #+#    #+#             */
/*   Updated: 2021/05/14 19:01:08 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	*rotate(float *centerxy, float *pointxy, float angle)
{
	float	*newxy;
	float	tmpx;
	float	tmpy;

	newxy = malloc(sizeof(float) * 2);
	angle = angle * -1;
	newxy[0] = pointxy[0] - centerxy[0];
	newxy[1] = pointxy[1] - centerxy[1];
	tmpx = newxy[0] * cos(angle) - newxy[1] * sin(angle);
	tmpy = newxy[0] * sin(angle) + newxy[1] * cos(angle);
	newxy[0] = tmpx + centerxy[0];
	newxy[1] = tmpy + centerxy[1];
	return (newxy);
}

#include <sys/time.h>

long long	get_time()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int		cub3d(t_mlx *data)
{
	long long current_time;

	current_time = get_time();
	if (current_time - data->last_time >= 1000 / 60)
	{
		clear_win(data);
		sky_box(data);
		get_distance(data);
		mlx_hook(data->win, 2, 1L<<0, keypress, data);
		mlx_hook(data->win, 3, 1L<<1, keyrelease, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		data->time += 0.00005;
		if (data->sneak < 100 && data->lookup == 1)
			data->sneak += 7;
		data->last_time = current_time;
		if (data->screenshot == 1)
		{
			data->screenshot = 0;
			take_screenshot(data);
		}
		event(data);
	}
	return (1);
}

void	test(t_mlx *data, char *str)
{
	if (init(data, str) == 0)
		return ;
	while (1)
	{
		mlx_loop_hook(data->mlx, cub3d, data);
		mlx_loop(data->mlx);
	}
}

int		main(int argc, char **argv)
{
	t_mlx	data;

	data.screenshot = 0;
	if (argc == 2 || (argc == 3 && ft_strcmp(argv[2], "--save") == 0))
	{
		if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		{
			data.screenshot = 1;
			bmp_header(&data, &data.bmpheader);
		}
		test(&data, argv[1]);
	}
	else
		ft_putstr("Usage ./cub3d map.cub || ./cub3d map.cub --save");
	return (1);
}
