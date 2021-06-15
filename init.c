/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:58:49 by agirona           #+#    #+#             */
/*   Updated: 2021/05/14 19:00:38 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_mlx *data, char *str)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_X, WIN_Y, str);
	if (data->win == NULL)
		return (error(data, 14, -1, 1));
	data->img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	if (data->img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		return (error(data, 15, -1, 1));
	}
	data->addr = (int *)mlx_get_data_addr(data->img,
			&data->bits, &data->linelen, &data->endian);
	return (1);
}

void	file_to_img(t_mlx *data)
{
	data->xpm[0].img = mlx_xpm_file_to_image(data->mlx,
			data->north + 1, &data->xpm[0].width, &data->xpm[0].height);
	data->xpm[1].img = mlx_xpm_file_to_image(data->mlx,
			data->south + 1, &data->xpm[1].width, &data->xpm[1].height);
	data->xpm[2].img = mlx_xpm_file_to_image(data->mlx,
			data->east + 1, &data->xpm[2].width, &data->xpm[2].height);
	data->xpm[3].img = mlx_xpm_file_to_image(data->mlx,
			data->west + 1, &data->xpm[3].width, &data->xpm[3].height);
	data->xpm[4].img = mlx_xpm_file_to_image(data->mlx,
			SPRITE, &data->xpm[4].width, &data->xpm[4].height);
	data->xpm[5].img = mlx_xpm_file_to_image(data->mlx,
			SKY, &data->xpm[5].width, &data->xpm[5].height);
	data->xpm[6].img = mlx_xpm_file_to_image(data->mlx,
			HAND, &data->xpm[6].width, &data->xpm[6].height);
	data->xpm[7].img = mlx_xpm_file_to_image(data->mlx,
			REV_SPRITE, &data->xpm[7].width, &data->xpm[7].height);
}

int	init_texture(t_mlx *data)
{
	int		i;

	i = 0;
	file_to_img(data);
	while (i < 8)
	{
		if (data->xpm[i].img == NULL)
		{
			error(data, 19, i, 1);
			while (--i >= 0)
				mlx_destroy_image(data->mlx, data->xpm[i].img);
			mlx_destroy_image(data->mlx, data->img);
			mlx_destroy_window(data->mlx, data->win);
			return (0);
		}
		data->xpm[i].addr = (int *)mlx_get_data_addr(data->xpm[i].img,
				&data->xpm[i].bpp, &data->xpm[i].size_line,
				&data->xpm[i].endian);
		i++;
	}
	return (1);
}

void	init_player(t_mlx *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->mapy)
	{
		x = -1;
		while (++x < data->mapx)
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
				data->px = x + 0.5;
				data->py = y + 0.5;
				data->map[y][x] = '0';
			}
		}
	}
}

int	init_struct(t_mlx *data)
{
	data->life = 100;
	data->fov = 60;
	data->cubesize = 1;
	data->proj = (WIN_X / 2) / tan((data->fov / 2) * (M_PI / 180));
	data->gap = (data->fov / WIN_X);
	data->pheight = WIN_Y / 2;
	data->alldist = malloc(sizeof(float) * WIN_X);
	data->frame = 1;
	data->ccolor = create_trgb(0, data->crgb[0], data->crgb[1], data->crgb[2]);
	data->fcolor = create_trgb(0, data->frgb[0], data->frgb[1], data->frgb[2]);
	if (data->alldist == NULL)
		return (error(data, 8, -1, 1));
	return (1);
}
