/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 18:44:24 by agirona           #+#    #+#             */
/*   Updated: 2021/06/15 17:04:08 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(t_mlx *data)
{
	int		i;
	int		c;
	char	**res;

	i = 0;
	c = 0;
	res = malloc(sizeof(char *) * data->mapy);
	if (res == NULL)
		return (NULL);
	while (i < data->mapy)
	{
		res[i] = malloc(sizeof(char) * data->mapx);
		if (res[i] == NULL)
		{
			while (i >= 0)
				free(res[i--]);
			free(res);
			return (NULL);
		}
		res[i] = ft_strncpy(res[i], data->map[c], data->mapx);
		i++;
		c++;
	}
	return (res);
}

int	get_map_size(t_mlx *data, char **info, int start)
{
	int		c;

	c = 0;
	while (start < data->infoline && info[start][0] == '\0')
		start++;
	if (start == data->infoline)
		return (error(data, 7, -1, 1));
	data->mapy = data->infoline - start;
	data->map = malloc(sizeof(char *) * data->mapy);
	if (data->map == NULL)
		return (error(data, 8, -1, 1));
	while (start < data->infoline)
	{
		if (data->mapx < (int)ft_strlen(info[start]))
			data->mapx = ft_strlen(info[start]);
		start++;
	}
	return (1);
}

int	get_map(t_mlx *data, char **info)
{
	int		i;
	int		c;

	i = data->infoline - data->mapy;
	c = 0;
	while (i < data->infoline)
	{
		data->map[c] = malloc(sizeof(char) * data->mapx);
		if (data->map[c] == NULL)
			return (error(data, 8, -1, 1));
		data->map[c] = ft_strncpy(data->map[c], info[i], data->mapx);
		i++;
		c++;
	}
	return (1);
}

int	check_map(t_mlx *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		if (data->map[y][0] == '\0')
			return (error(data, 9, data->infoline - data->mapy + y + 1, 1));
		while (x < data->mapx)
		{
			if (data->map[y][x] != '\0'
					&& ft_ischar(" 012NEWS", data->map[y][x]) == 0)
				return (error(data, 10, data->infoline
						- data->mapy + y + 1, 1));
			x++;
		}
		y++;
	}
	return (1);
}

int	spam_fill(t_mlx *data, char **map, int x, int y)
{
	if (x < 0 || x >= data->mapx || y < 0 || y >= data->mapy)
		return (0);
	if (map[y][x] == '.' || map[y][x] == '1')
		return (1);
	if (ft_ischar("NEWS02", map[y][x]) == 1)
		map[y][x] = '.';
	if (spam_fill(data, map, x + 1, y) == 1
		&& spam_fill(data, map, x - 1, y) == 1
		&& spam_fill(data, map, x, y + 1) == 1
		&& spam_fill(data, map, x, y - 1) == 1)
		return (1);
	else
		return (0);
}
