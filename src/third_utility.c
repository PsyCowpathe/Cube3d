/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:20:57 by agirona           #+#    #+#             */
/*   Updated: 2021/06/21 17:44:43 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_it_possible(t_mlx *data, float *tmp)
{
	float	x;
	float	y;

	x = data->px;
	y = data->py;
	while (x < tmp[0] && y > tmp[1])
	{
		x += 0.05;
		y -= 0.05;
		if (!ft_ischar("02", data->map[(int)y][(int)x]))
			return (0);
	}
	while (x < tmp[0] && y < tmp[1])
	{
		x += 0.05;
		y += 0.05;
		if (!ft_ischar("02", data->map[(int)y][(int)x]))
			return (0);
	}
	return (1);
}

int	is_possible(t_mlx *data, float *tmp)
{
	float	x;
	float	y;

	x = data->px;
	y = data->py;
	while (x > tmp[0] && y > tmp[1])
	{
		x -= 0.05;
		y -= 0.05;
		if (!ft_ischar("02", data->map[(int)y][(int)x]))
			return (0);
	}
	while (x > tmp[0] && y < tmp[1])
	{
		x -= 0.05;
		y += 0.05;
		if (!ft_ischar("02", data->map[(int)y][(int)x]))
			return (0);
	}
	return (is_it_possible(data, tmp));
}

int	choose_text(t_mlx *data, int x)
{
	int		texture;

	texture = 0;
	if (data->hdist < data->vdist)
	{
		data->alldist[x] = data->hdist;
		texture = 0;
		if (data->hory >= (int)data->hory + 0.5)
			texture = 1;
	}
	else
	{
		data->alldist[x] = data->vdist;
		texture = 3;
		if (data->vertx >= (int)data->vertx + 0.5)
			texture = 2;
	}
	return (texture);
}

int	end_verif(char *str, int nb, int *i)
{
	if ((nb == 2 && str[*i] != '\0')
		|| (nb != 2 && !(str[*i] == ',' && (str[*i + 1] == ' '
					|| ft_ischar("0123456789", str[*i + 1])))))
		return (0);
	if (str[*i] && str[*i] == ',')
		*i = *i + 1;
	return (1);
}

int	hav_path(t_mlx *data, int check)
{
	if (check == 0)
	{
		if (data->no > 0 && data->so > 0 && data->ea > 0
			&& data->we > 0 && data->f > 0 && data->c > 0)
			return (1);
	}
	else
	{
		if (data->no > 1 || data->so > 1 || data->ea > 1
			|| data->we > 1 || data->f > 1 || data->c > 1)
			return (error(data, 17, -1, 1));
		if (data->no > 0 && data->so > 0 && data->ea > 0
			&& data->we > 0 && data->f > 0 && data->c > 0)
		{
			if (data->north == NULL || data->south == NULL
				|| data->east == NULL || data->west == NULL)
				return (error(data, 8, -1, 1));
			return (1);
		}
		return (error(data, 18, -1, 1));
	}
	return (0);
}
