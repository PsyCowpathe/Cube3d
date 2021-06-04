/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:46:35 by agirona           #+#    #+#             */
/*   Updated: 2021/05/14 14:45:58 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		tmp(t_mlx *data);

int		tmp(t_mlx *data)
{
	event(data);
	return (1);
}

void	game_run(t_mlx *data, char *str)
{
	if (init(data, str) == 0)
		return ;
	if (sprite(data) == 0)
		data->end = 1;
	if (data->screenshot == 1)
		take_screenshot(data);
	mlx_hook(data->win, 2, 1L<<0, keypress, data);
	mlx_hook(data->win, 3, 1L<<1, keyrelease, data);
	mlx_loop_hook(data->mlx, &tmp, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
}

int		main(int argc, char **argv)
{
	t_mlx	data;

	data.screenshot = 0;
	float	res;

	res = atan2(6, 6);
	if (argc == 2 || (argc == 3 && ft_strcmp(argv[2], "--save") == 0))
	{
		if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		{
			data.screenshot = 1;
			bmp_header(&data, &data.bmpheader);
		}
		game_run(&data, argv[1]);
	}
	else
		ft_putstr("Usage ./cub3d map.cub || ./cub3d map.cub --save");
	return (1);
}
