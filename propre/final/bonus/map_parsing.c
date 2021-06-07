/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 18:44:24 by agirona           #+#    #+#             */
/*   Updated: 2021/06/07 15:56:14 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	get_map(t_mlx *data, char **info, int l2)
{
	int		l1;
	int		max;

	l1 = 0;
	max = 0;
	data->map = malloc(sizeof(char *) * data->infoline - l2);
	if (data->map == NULL)
		return (error(data, 9, -1));
	while (l1 < data->infoline)
	{
		if (max < (int)ft_strlen(info[l1]))
			max = ft_strlen(info[l1]);
		l1++;
	}
	data->mapy = data->infoline - l2;
	data->mapx = max;
	l1 = 0;
	while (l2 < data->infoline)
	{
		data->map[l1] = malloc(sizeof(char) * max);
		if (data->map[l1] == NULL)
			return (error(data, 9, -1));
		data->map[l1] = ft_strncpy(data->map[l1], info[l2], max);
		l1++;
		l2++;
	}
	return (1);
}

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
			return (NULL);
		res[i] = ft_strncpy(res[i], data->map[c], data->mapx);
		ft_putstr(res[i]);
		ft_putchar('\n');
		i++;
		c++;
	}
	return (res);
}
