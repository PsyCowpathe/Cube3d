/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:02:00 by agirona           #+#    #+#             */
/*   Updated: 2021/06/13 19:10:07 by agirona          ###   ########lyon.fr   */
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
	if (line[i] == 'N' && line[i + 1] == 'O' && ++find && ++data->no < 2 )
		data->north = ft_strdup(line + i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ++find && ++data->so < 2)
		data->south = ft_strdup(line + i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ++find && ++data->we < 2)
		data->west = ft_strdup(line + i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ++find && ++data->ea < 2)
		data->east = ft_strdup(line + i + 2);
	else if (line[i] == 'F' && ++find && ++data->f < 2)
		data->floor = ft_strdup(line + i + 1);
	else if (line[i] == 'C' && ++find && ++data->c < 2)
		data->ceiling = ft_strdup(line + i + 1);
	if (find != 0 && i != 0)
		return (error(data, 2, nb + 1, 1));
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

int	line_and_path(t_mlx *data, char **info)
{
	int		i;
	int		ret;
	int		map;

	i = 0;
	if (info[i][0] == '\0')
		return (error(data, 1, -1, 1));
	if (info[data->infoline - 1][0] == '\0')
		return (error(data, 3, -1, 1));
	while (i <= data->infoline)
	{
		ret = get_path(data, info[i], i);
		if (ret == 0)
			return (0);
		if (ret == 1 && hav_path(data, 0) == 0 && info[i][0] != '\0')
		{
			error(data, 18, -1, 1);
			return (error(data, 4, i + 1, 0));
		}
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
			return (error(data, 5 + invalid, -1, 1));
		c = 0;
		while (s[i] && ft_ischar("0123456789", s[i]) == 1 && c < 3)
			tmp[c++] = s[i++];
		tmp[c] = '\0';
		rgb[++nb] = ft_atoi(tmp);
		if ((nb == 2 && s[i] != '\0') || (nb != 2 && !(s[i] == ','
					&& (s[i + 1] == ' ' || ft_ischar("0123456789", s[i + 1])))))
			return (error(data, 5 + invalid, -1, 1));
		if (s[i] && s[i] == ',')
			i++;
		while (nb != 2 && s[i] && s[i] == ' ')
			i++;
	}
	return (check_color(data, rgb, invalid));
}

int	parsing(t_mlx *data, char *str)
{
	char	**cpy;
	int		map;

	data->info = get_file_size(data, str);
	if (data->info == NULL)
		return (error(data, 8, -1, 1));
	map = line_and_path(data, data->info);
	if (map == 0)
		return (0);
	if (get_color(data, data->floor, data->frgb, 0) == 0)
		return (0);
	if (get_color(data, data->ceiling, data->crgb, 1) == 0)
		return (0);
	if (get_map_size(data, data->info, map + 1) == 0)
		return (0);
	if (!get_map(data, data->info) || !check_map(data) || !verif_player(data))
		return (0);
	init_player(data);
	cpy = copy_map(data);
	if (cpy == NULL)
		return (error(data, 8, -1, 1));
	if (spam_fill(data, cpy, data->px, data->py) == 0)
		return (error(data, 13, -1, 1));
	int		v = 0;
	while (v < data->mapy)
		free(cpy[v++]);
	free(cpy);
	return (1);
}
