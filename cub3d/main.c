/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:22:57 by agirona           #+#    #+#             */
/*   Updated: 2021/04/19 11:04:57 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map, int max)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < max)
	{
		while (map[y][x])
			ft_putchar(map[y][x++]);
		x = 0;
		ft_putchar('\n');
		y++;
	}
}

void	square(t_mlx *data, int x, int y, int size, int color)
{
	int		i;

	i = 0;
	while (i < size)
	{
		set_pixel(data, x + i, y, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		set_pixel(data, x, y + i, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		set_pixel(data, x + size, y + i, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		set_pixel(data, x + i, y + size, color);
		i++;
	}
}

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

void	mini_map(t_mlx *data, int size)
{
	int		x;
	int		y;
	float	centerxy[2];
	float	pointxy[2];
	float	*tmp;
	int		*tab;

	y = 0;
	tab = malloc(sizeof(int) * 4);
	while (y <= 6)
	{
		x = 0;
		while (x <= 18)
		{
			if (data->map[y][x] == '1')
				square(data, x * size, y * size, size, WHITE);
			x++;
		}
		y++;
	}
	square(data, (int)data->px * size, (int)data->py * size, size, RED);
	centerxy[0] = data->px * 20;
	centerxy[1] = data->py * 20;
	pointxy[0] = (data->px * 20) + 30;
	pointxy[1] = data->py * 20;
	tmp = rotate(centerxy, pointxy, (data->pa - 30) * (M_PI / 180));
	tab[0] = centerxy[0];
	tab[1] = centerxy[1];
	tab[2] = (int)tmp[0];
	tab[3] = (int)tmp[1];
	draw_utility(tab, data);
	free(tmp);
	tmp = rotate(centerxy, pointxy, (data->pa + 30) * M_PI / 180);
	tab[0] = centerxy[0];
	tab[1] = centerxy[1];
	tab[2] = (int)tmp[0];
	tab[3] = (int)tmp[1];
	free(tmp);
	draw_utility(tab, data);
	free(tab);
}

void	texture(t_mlx *data)
{
	int		img_width;
	int		img_height;
	int		y;
	int		x;
	int		bpp;
	int		endian;
	int		size_line;

	y = 0;
	x = 0;
    data->texture = mlx_xpm_file_to_image(data->mlx, "/Users/agirona/stud/Cub3D/textures/test.xpm", &img_width, &img_height);
	data->text_data = (int *)mlx_get_data_addr(data->texture, &bpp, &size_line, &endian);
	while (y < 64)
	{
		while (x < 64)
		{
			data->addr[y * WIN_X + x] = data->text_data[y * 64 + x];
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int		event(t_mlx *data)
{
	float	*tmp;
	float	centerxy[2];
	float	pointxy[2];

	clear_win(data);
	if (data->forward == 1)
	{
		centerxy[0] = data->px;
		centerxy[1] = data->py;
		pointxy[0] = data->px + 0.1;
		pointxy[1] = data->py;
		tmp = rotate(centerxy, pointxy, data->pa * (M_PI / 180));
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
		pointxy[0] = data->px + 0.1;
		pointxy[1] = data->py;
		tmp = rotate(centerxy, pointxy, (data->pa - 90) * (M_PI / 180));
		if (data->map[(int)tmp[1]][(int)tmp[0]] == '0')
		{
			data->px = tmp[0];
			data->py = tmp[1]; 
		}
	}
	if (data->left == 1)
	{
		centerxy[0] = data->px;
		centerxy[1] = data->py;
		pointxy[0] = data->px + 0.1;
		pointxy[1] = data->py;
		tmp = rotate(centerxy, pointxy, (data->pa + 90) * (M_PI / 180));
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
		pointxy[0] = data->px + 0.1;
		pointxy[1] = data->py;
		tmp = rotate(centerxy, pointxy, (data->pa - 180) * (M_PI / 180));
		if (data->map[(int)tmp[1]][(int)tmp[0]] == '0')
		{
			data->px = tmp[0];
			data->py = tmp[1]; 
		}
	}
	if (data->turnright == 1)
	{
		data->pa -= ROT;
		if (data->pa < 0)
			data->pa = 360 + data->pa;
	}
	if (data->turnleft == 1)
	{
		data->pa += ROT;
		if (data->pa > 360)
			data->pa = 0 + (data->pa - 360);
	}
	calc_distance(data);
	mini_map(data, 20);
	texture(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (1);
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
	event(data);
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
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx	data;

	if (argc == 2 || (argc == 3 && ft_strcmp(argv[2], "--save") == 0))
	{
		init_mlx(&data, argv[1]);
		if (read_map(argv[1], &data) == 0)
			return (0);
		clear_win(&data);
		init_player(&data);
		data.px = 3.5;
		data.py = 2.5;
		calc_distance(&data);
		mini_map(&data, 20);
		mlx_hook(data.win, 2, 1L<<0, keypress, &data);
		mlx_hook(data.win, 3, 1L<<1, keyrelease, &data);
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_loop(data.mlx);
	}
	else
		ft_putstr("Usage ./cub3d map.cub || ./cub3d map.cub --save");
	return (1);
}
