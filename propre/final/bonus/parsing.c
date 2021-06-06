/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:02:00 by agirona           #+#    #+#             */
/*   Updated: 2021/06/06 19:32:02 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_line_form(t_mlx *data, char **info, int i, int *map)
{
	if (info[i][0] == ' ' && hav_path(data) == 0)
		return (error(data, 2, i + 1));
	if (*map > 0 && info[i][0] == '\0' && hav_path(data) == 1
			&& i != data->infoline)
		return (error(data, 5, i + 1));
	if (hav_path(data) == 1 && info[i][0] != '\0' && *map == 0)
		*map = i;
	if (i == data->infoline - 1 && info[i][0] == '\0')
		return (error(data, 4, -1));
	//if (is_map(data, info[i]) == 1 && info[i][0] != '\0'
	//		&& hav_path(data) == 0)
	//	return (error(data, 7, i + 1));
	return (1);
}

int	verif_form(char **info, t_mlx *data)
{
	int		i;
	int		c;
	int		map;

	i = -1;
	if (info[i + 1][0] == '\0')
		return (error(data, 1, -1));
	map = 0;
	while (++i <= data->infoline)
	{
		if (verif_line_form(data, info, i, &map) == 0)
			return (0);
		c = -1;
		while (info[i][++c] != '\0')
		{
			if (info[i][c + 1] == '\0' && info[i][c] == ' ')
				return (error(data, 3, i + 1));
			if (map > 0 && ft_ischar(" 012NSEW", info[i][c]) == 0)
				return (error(data, 7, i + 1));
		}
	}
	if (hav_path(data) == 0)
		return (error(data, 6, -1));
	if (hav_path(data) == 1 && get_map(data, info, map) == 0)
		return (0);
	return (1);
}

int	verif_info(t_mlx *data, char *str, int invalid)
{
	int		i;
	int		c;
	int		rgb;
	char	tmp[4];

	i = 0;
	rgb = 0;
	while (str[i] == ' ')
		i++;
	if (i == 0)
		return (error(data, 10, invalid));
	while (str[i])
	{
		if (ft_ischar("0123456789", str[i]) == 0)
			return (error(data, 8, invalid));
		c = 0;
		while (str[i] && ft_ischar("0123456789", str[i]) == 1)
			tmp[c++] = str[i++];
		tmp[c] = '\0';
		data->frgb[rgb] = ft_atoi(tmp);
		if (!(data->frgb[rgb] >= 0 && data->frgb[rgb] <= 255))
			return (error(data, 9, -1));
		if (rgb != 2 && !(str[i] == ',' && (str[i + 1] == ' '
					|| ft_ischar("0123456789", str[i + 1]))))
			return (error(data, 8, invalid));
		while (rgb != 2 && str[i] && ft_ischar("0123456789", str[i]) == 0)
			i++;
		if (rgb == 2 && i != (int)ft_strlen(str))
			return (error(data, 8, invalid));
		rgb++;
	}
	return (1);
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
		return (error(data, 15, -1));
	return (1);
}

int	parsing(t_mlx *data, char *str)
{
	char	**info;
	char	**cpy;

	data->north = 0;
	data->south = 0;
	data->east = 0;
	data->west = 0;
	data->floor = 0;
	data->ceiling = 0;
	info = get_file_size(data, str);
	if (info == NULL)
		return (0);
	if (verif_form(info, data) == 0)
		return (0);
	if (data->no > 1 || data->so > 1 || data->ea > 1
		|| data->we > 1 || data->f > 1 || data->c > 1)
		return (error(data, 11, -1));
	if (verif_info(data, data->floor, 0) == 0)
		return (0);
	if (verif_info(data, data->ceiling, 1) == 0)
		return (0);
	if (verif_player(data) == 0)
		return (0);
	init_player(data);
	cpy = copy_map(data);
	if (cpy == NULL)
		return (error(data, 12, -1));
	if (spam_fill(data, cpy, data->px, data->py) == 0)
		return (error(data, 14, -1));
	return (1);
}
