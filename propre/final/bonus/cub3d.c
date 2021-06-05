/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:46:35 by agirona           #+#    #+#             */
/*   Updated: 2021/06/05 20:58:44 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init(t_mlx *data, char *str)
{
	if (init_mlx(data, str) == 0)
		return (0);
	if (init_texture(data) == 0)
		return (0);
	if (init_struct(data) == 0)
		return (0);
	init_player(data);
	data->count = sprite_count(data);
	data->sprite = malloc(sizeof(t_sprite) * data->count);
	if (data->sprite == NULL)
		return (0);
	get_sprite_position(data, data->sprite);
	return (1);
}

void	raycasting(t_mlx *data)
{
	int		x;
	float	ray;
	float	patch;

	x = WIN_X - 1;
	patch = (data->fov * -.5f) * -1;
	ray = data->looking - (data->fov / 2);
	while (x >= 0)
	{
		if (ray < 0)
			ray = 360 + ray;
		else if (ray > 360)
			ray = 0 + (ray - 360);
		get_first_hor(data, ray);
		get_first_vert(data, ray);
		get_closest_vertical_wall(data, ray);
		get_closest_horizontal_wall(data, ray);
		get_closest_wall(data, x, data->looking - ray);
		patch = patch + data->gap;
		ray = ray + data->gap;
		x--;
	}
}

int	refresh(t_mlx *data)
{
	long long	current_time;

	current_time = get_time();
	if (current_time - data->last_time >= 1000 / 60)
	{
		if (data->tick > 30)
			data->tick = 1;
		data->tick++;
		event(data);
		if (data->save == 1)
		{
			data->end = 1;
			take_screenshot(data);
		}
		data->time += 1;
		data->last_time = current_time;
	}
	return (1);
}

void	game_run(t_mlx *data, char *str)
{
	if (parsing(data, str) == 0)
		return ;
	if (init(data, str) == 0)
		return ;
	if (sprite(data) == 0)
		data->end = 1;
	//system("afplay ../../../sound/musique.mp3 -v 0.1 &");
	mlx_hook(data->win, 2, 1L << 0, keypress, data);
	mlx_hook(data->win, 3, 1L << 1, keyrelease, data);
	mlx_loop_hook(data->mlx, &refresh, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	data;

	data.screenshot = 0;
	if (argc == 2 || (argc == 3 && ft_strcmp(argv[2], "--save") == 0))
	{
		if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		{
			data.save = 1;
			bmp_header(&data, &data.bmpheader);
		}
		game_run(&data, argv[1]);
	}
	else
		ft_putstr("Usage ./cub3d map.cub || ./cub3d map.cub --save");
	return (1);
}
