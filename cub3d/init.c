/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:52:18 by agirona           #+#    #+#             */
/*   Updated: 2021/04/19 13:11:34 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_mlx *data, char *str)
{
	int		bpp;
	int		endian;
	int		size_line;
	int		img_width;
	int		img_height;
	
	data->mapy = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_X, WIN_Y, str);
	data->img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits,
			&data->linelen, &data->endian);

	data->texture = mlx_xpm_file_to_image(data->mlx, "/Users/agirona/stud/Cub3D/textures/test.xpm", &img_width, &img_height);
	data->text_data = (int *)mlx_get_data_addr(data->texture, &bpp, &size_line, &endian);

}

void	init_player(t_mlx *data)
{
	int		x;
	int		y;

	y = 0;
	data->fov = 60;
	data->cubesize = 1;
	data->proj = WIN_X / tan(30 * (M_PI / 180));
	data->between = (data->fov / WIN_X);
	while (y < data->mapy)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == 'E')
				data->pa = 0;
			if (data->map[y][x] == 'N')
				data->pa = 90;
			if (data->map[y][x] == 'W')
				data->pa = 180;
			if (data->map[y][x] == 'S')
				data->pa = 270;
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
