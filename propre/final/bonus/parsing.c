/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:02:00 by agirona           #+#    #+#             */
/*   Updated: 2021/06/05 20:58:36 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_map(t_mlx *data, char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == 'N' && str[i + 1] == 'O' && ++data->no)
		data->north = ft_strdup(str + i + 2);
	if (str[i] == 'S' && str[i + 1] == 'O' && ++data->so)
		data->south = ft_strdup(str + i + 1);
	if (str[i] == 'W' && str[i + 1] == 'E' && ++data->we)
		data->west = ft_strdup(str + i + 1);
	if (str[i] == 'E' && str[i + 1] == 'A' && ++data->ea)
		data->east = ft_strdup(str + i + 1);
	if (str[i] == 'F' && ++data->f)
		data->floor = ft_strdup(str + i + 1);
	if (str[i] == 'C' && ++data->c)
		data->ceiling = ft_strdup(str + i + 1);
	if ((str[i] == 'N' && str[i + 1] == 'O') || (str[i] == 'S' && str[i + 1] == 'O')
			|| (str[i] == 'W' && str[i + 1] == 'E') 
			|| (str[i] == 'E' && str[i + 1] == 'A')
			|| (str[i] == 'F' || str[i] == 'C'))
		return (0);
	return (1);
}


int		get_map(t_mlx *data, char **info, int l2)
{
	int		l1;
	int		c1;
	int		c2;
	int		max;

	l1 = 0;
	c1 = l2;
	max = 0;
	data->map = malloc(sizeof(char *) * data->infoline - l2);
	if (data->map == NULL)
		return (error(data, 12, -1));
	while (c1 < data->infoline)
	{
		if (max < (int)ft_strlen(info[c1]))
				max = ft_strlen(info[c1]);
		c1++;
	}
	data->mapy = data->infoline - l2;
	data->mapx = max;
	data->px = -1;
	data->py = -1;
	ft_putnbr(data->mapy);
	while (l2 < data->infoline)
	{
		c1 = 0;
		c2 = 0;
		data->map[l1] = malloc(sizeof(char) * max);
		if (data->map[l1] == NULL)
			return (error(data, 12, -1));
		data->map[l1][max - 1] = '\0';
		ft_memset(data->map[l1], '1', max);
		while (c2 < max)
		{
			if (c2 < (int)ft_strlen(info[l2]))
			{
				if (c2 < (int)ft_strlen(info[l2]) && info[l2][c2] == ' ')
					info[l2][c2] = '1';
				data->map[l1][c1] = info[l2][c2];
			}
			if (ft_ischar("NEWS", data->map[l1][c1]) == 1)
			{
				data->py = l1;
				if (data->px == -1)
					data->px = c1;
				else
					return (error(data, 13, -1));
			}
			c2++;
			c1++;
		}
		l1++;
		l2++;
	}
	return (1);
}

int		verif_form(char **info, t_mlx *data)
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
		if (info[i][0] == ' ' && hav_path(data) == 0)
			return (error(data, 2, i + 1));
		if (hav_path(data) == 1 && info[i][0] != '\0' && map == 0)
			map = i;
		if (map > 0 && info[i][0] == '\0' && hav_path(data) == 1 && i != data->infoline)
			return (error(data, 5, i + 1));
		if (is_map(data, info[i]) == 1 && info[i][0] != '\0' && hav_path(data) == 0)
			return (error(data, 7, i + 1));
		if (i == data->infoline - 1 && info[i][0] == '\0')
			return (error(data, 4, -1));
		c = -1;
		while (info[i][++c] != '\0')
		{
			ft_putchar(info[i][c]);
			if (info[i][c + 1] == '\0' && info[i][c] == ' ')
				return (error(data, 3, i + 1));
			if (map > 0 && ft_ischar(" 012NSEW", info[i][c]) == 0)
				return (error(data, 7, i + 1));
		}
		ft_putchar('\n');
	}
	if (hav_path(data) == 0)
		return (error(data, 6, -1));
	if (get_map(data, info, map) == 0)
		return (0);
	return (1);
}

int		verif_info(t_mlx *data, char *str, int invalid)
{
	int	i;
	int	c;
	int	rgb;
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

//int		spam_fill(char **map)
//{

//}

int		parsing(t_mlx *data, char *str)
{
	char	**info;

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
	//if (spam_fill(data->map) == 0)
		//return (0);
	return (1);
}
