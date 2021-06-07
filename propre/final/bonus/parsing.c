/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:02:00 by agirona           #+#    #+#             */
/*   Updated: 2021/06/07 20:38:38 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_path(t_mlx *data, char *line, int nb)
{
	int		i;
	int		find;

	i = 0;
	find = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && ++data->no && ++find)
		data->north = ft_strdup(line + i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ++data->so && ++find)
		data->south = ft_strdup(line + i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ++data->we && ++find)
		data->west = ft_strdup(line + i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ++data->ea && ++find)
		data->east = ft_strdup(line + i + 2);
	else if (line[i] == 'F' && ++data->f && ++find)
		data->floor = ft_strdup(line + i + 1);
	else if (line[i] == 'C' && ++data->c && ++find)
		data->ceiling = ft_strdup(line + i + 1);
	if (find != 0 && i != 0)
		return (error(data, 2, nb + 1));
	if (find == 0)
		return (1);
	return (2);
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
			return (error(data, 5, -1));
		if (data->no > 0 && data->so > 0 && data->ea > 0
			&& data->we > 0 && data->f > 0 && data->c > 0)
		{
			if (data->north == NULL || data->south == NULL
				|| data->east == NULL || data->west == NULL)
				return (error(data, 9, -1));
			return (1);
		}
		return (error(data, 6, -1));
	}
	return (0);
}

int	check_path(t_mlx *data)
{
	if (data->north[0] != ' ')
		return (error(data, 4, 0));
	if (data->south[0] != ' ')
		return (error(data, 4, 1));
	if (data->east[0] != ' ')
		return (error(data, 4, 2));
	if (data->west[0] != ' ')
		return (error(data, 4, 3));
	if (data->floor[0] != ' ')
		return (error(data, 4, 4));
	if (data->ceiling[0] != ' ')
		return (error(data, 4, 5));
	return (1);
}

int	line_and_path(t_mlx *data, char **info)
{
	int		i;
	int		ret;
	int		map;

	i = 0;
	if (info[i][0] == '\0')
		return (error(data, 1, -1));
	if (info[data->infoline - 1][0] == '\0')
		return (error(data, 3, -1));
	while (i <= data->infoline )
	{
		ret = get_path(data, info[i], i);
		if (ret == 0)
			return (0);
		if (ret == 1 && hav_path(data, 0) == 0 && info[i][0] != '\0')
			return (error(data, 7, i + 1));
		if (ret == 2)
			map = i;
		i++;
	}
	if (hav_path(data, 1) == 0)
		return (0);
	if (check_path(data) == 0)
		return (0);
	return (map);
}

int	check_color(t_mlx *data, int *rgb, int invalid)
{
	int		nb;

	nb = 0;
	while (nb < 3)
	{
		if (rgb[nb] < 0 || rgb[nb] > 255)
			return (error(data, 8, invalid));
		nb++;
	}
	return (1);
}

int	get_color(t_mlx *data, char *s, int *rgb, int invalid)
{
	int		i;
	int		c;
	int		nb;
	char	tmp[4];

	i = 0;
	nb = -1;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (ft_ischar("0123456789", s[i]) == 0)
			return (error(data, 4, 4 + invalid));
		c = 0;
		while (s[i] && ft_ischar("0123456789", s[i]) == 1 && c < 3)
			tmp[c++] = s[i++];
		tmp[c] = '\0';
		rgb[++nb] = ft_atoi(tmp);
		if ((nb == 2 && s[i] != '\0') || (nb != 2 && !(s[i] == ','
					&& (s[i + 1] == ' ' || ft_ischar("0123456789", s[i + 1])))))
			return (error(data, 8, invalid));
		while (nb != 2 && s[i] && ft_ischar("0123456789", s[i]) == 0)
			i++;
	}
	return (check_color(data, rgb, invalid));
}

int	verif_player(t_mlx *data)
{
	int		i;
	int		c;
	int		count;

	i = 0;
	count = 0;
	while (i < data->mapy)
	{
		c = 0;
		while (c < data->mapx)
		{
			if (ft_ischar("NEWS", data->map[i][c]) == 1)
				count++;
			c++;
		}
		i++;
	}
	if (count > 1)
		return (error(data, 13, -1));
	if (count < 1)
		return (error(data, 14, -1));
	return (1);
}

int	get_map_size(t_mlx *data, char **info, int start)
{
	int		c;

	c = 0;
	while (start < data->infoline && info[start][0] == '\0')
		start++;
	if (start == data->infoline - 1)
		return (error(data, 10, -1));
	data->mapy = data->infoline - start;
	data->map = malloc(sizeof(char *) * data->mapy);
	if (data->map == NULL)
		return (error(data, 9, -1));
	data->mapx = 0;
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
			return (error(data, 9, -1));
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
			return (error(data, 11, data->infoline - data->mapy + y + 1));
		while (x < data->mapx)
		{
			if (data->map[y][x] != '\0' && ft_ischar(" 012NEWS", data->map[y][x]) == 0)
				return (error(data, 12, data->infoline - data->mapy + y + 1)); 
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
int	parsing(t_mlx *data, char *str)
{
	char	**info;
	char	**cpy;
	int		map;

	data->north = 0;
	data->south = 0;
	data->east = 0;
	data->west = 0;
	data->floor = 0;
	data->ceiling = 0;
	info = get_file_size(data, str);
	if (info == NULL)
		return (0);
	map = line_and_path(data, info);
	if (map == 0)
		return (0);
	if (get_color(data, data->floor, data->frgb, 0) == 0)
		return (0);
	if (get_color(data, data->ceiling, data->crgb, 1) == 0)
		return (0);
	if (get_map_size(data, info, map + 1) == 0)
		return (0);
	if (get_map(data, info) == 0)
		return (0);
	if (check_map(data) == 0)
		return (0);
	if (verif_player(data) == 0)
		return (0);
	init_player(data);
	cpy = copy_map(data);
	if (cpy == NULL)
		return (error(data, 9, -1));
	if (spam_fill(data, cpy, data->px, data->py) == 0)
		return (error(data, 15, -1));
	return (1);
}
