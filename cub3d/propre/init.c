/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:21:58 by agirona           #+#    #+#             */
/*   Updated: 2021/05/14 15:21:42 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_mlx(t_mlx *data, char *str)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_X, WIN_Y, str);
	if (data->win == NULL)
		return (0);
	data->img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	if (data->img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		return (0);
	}
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits, &data->linelen, &data->endian);
	return (1);
}

int		init_texture(t_mlx *data)
{
	int		i;

	i = 0;
	data->xpm[0].img = mlx_xpm_file_to_image(data->mlx, NORTH, &data->xpm[0].img_width, &data->xpm[0].img_height);
	data->xpm[1].img = mlx_xpm_file_to_image(data->mlx, SOUTH, &data->xpm[1].img_width, &data->xpm[1].img_height);
	data->xpm[2].img = mlx_xpm_file_to_image(data->mlx, EAST, &data->xpm[2].img_width, &data->xpm[2].img_height);
	data->xpm[3].img = mlx_xpm_file_to_image(data->mlx, WEST, &data->xpm[3].img_width, &data->xpm[3].img_height);
	data->xpm[4].img = mlx_xpm_file_to_image(data->mlx, SPRITE, &data->xpm[4].img_width, &data->xpm[4].img_height);
	data->xpm[5].img = mlx_xpm_file_to_image(data->mlx, SKY, &data->xpm[5].img_width, &data->xpm[5].img_height);
	while (i < 6)
	{
		if (data->xpm[i].img == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(data->mlx, data->xpm[i].img);
			mlx_destroy_image(data->mlx, data->img);
			mlx_destroy_window(data->mlx, data->win);
			return (0);
		}
		data->xpm[i].addr = (int *)mlx_get_data_addr(data->xpm[i].img, &data->xpm[i].bpp,
		&data->xpm[i].size_line, &data->xpm[i].endian);
		i++;
	}
	return (1);
}

void	init_player(t_mlx *data)
{
	int		x;
	int		y;

	y = 0;
	data->fov = 60;
	data->cubesize = 1;
	data->proj = (WIN_X / 2) / tan(30 * (M_PI / 180));
	data->gap = (data->fov / WIN_X);
	data->pheight = WIN_Y / 2;
	data->time = 0;
	data->sneak = 0;
	data->firstx = -1;
	data->lastx = -1;
	data->last_time = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == 'E')
				data->looking = 0;
			if (data->map[y][x] == 'N')
				data->looking = 90;
			if (data->map[y][x] == 'W')
				data->looking = 180;
			if (data->map[y][x] == 'S')
				data->looking = 270;
			if (ft_ischar("NEWS", data->map[y][x]) == 1)
			{
				data->px = x * data->cubesize;
				data->py = y * data->cubesize;
				data->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

int		init(t_mlx *data, char *str)
{
	
	if (read_map(str, data) == 0)
		return (0);
	if (init_mlx(data, str) == 0)
		return (0);
	if (init_texture(data) == 0)
		return (0);
	data->end = 0;
	init_player(data);
	return (1);
}

