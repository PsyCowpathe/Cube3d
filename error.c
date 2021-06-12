/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 19:09:50 by agirona           #+#    #+#             */
/*   Updated: 2021/06/12 15:33:38 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*g_error_list[] =
{
	"Empty line at start of file.",
	"Space at start of line : ",
	"Empty line at end of file.",
	"Invalid characters at line : ",
	"Color of floor isnt correctly formated. \
		\nTips : Color must be between 0 and 255.",
	"Color of ceiling isnt correctly formated. \
		\nTips : Color must be between 0 and 255.",
	"Missing map at bottom of the file.",
	"Malloc allocation failed",
	"Empty line in map at line : ",
	"Invalid characters in map at line : ",
	"Sorry but this game doesnt support multiplayer =) \
		\nPlease set only one spawn point.",
	"Game cant start without you ;)\nPlease set a spawn point.",
	"Map isnt closed !",
};

void	last_error(t_mlx *data, int nb)
{
	if (nb == 16)
	{
		if (data->no == 0)
			ft_putstr("Missing north texture.\n");
		if (data->so == 0)
			ft_putstr("Missing south texture.\n");
		if (data->ea == 0)
			ft_putstr("Missing east texture.\n");
		if (data->we == 0)
			ft_putstr("Missing west texture.\n");
		if (data->f == 0)
			ft_putstr("Missing floor color.\n");
		if (data->c == 0)
			ft_putstr("Missing ceiling color.\n");
	}
}

void	advanced_error2(t_mlx *data, int nb)
{
	if (nb == 15)
	{
		if (data->no > 1)
			ft_putstr("Redefinition of north texture.\n");
		if (data->so > 1)
			ft_putstr("Redefinition of south texture.\n");
		if (data->ea > 1)
			ft_putstr("Redefinition of east texture.\n");
		if (data->we > 1)
			ft_putstr("Redefinition of west texture.\n");
		if (data->f > 1)
			ft_putstr("Redefinition of floor color.\n");
		if (data->c > 1)
			ft_putstr("Redefinition of ceiling color.\n");
	}
	else
		last_error(data, nb);
}

void	advanced_error(t_mlx *data, int nb, int line)
{
	if (nb == 14)
	{
		if (line == 0)
			ft_putstr("Invalid characters in north declaration.");
		else if (line == 1)
			ft_putstr("Invalid characters in south declaration.");
		else if (line == 2)
			ft_putstr("Invalid characters in east declaration.");
		else if (line == 3)
			ft_putstr("Invalid characters in west declaration.");
		else if (line == 4)
			ft_putstr("Invalid characters in floor declaration.");
		else if (line == 5)
			ft_putstr("Invalid characters in ceiling declaration.");
	}
	else
		advanced_error2(data, nb);
}

int	error(t_mlx *data, int nb, int line)
{
	ft_putstr("Error\n");
	if (nb >= 1 && nb <= 13)
	{
		nb = nb - 1;
		ft_putstr((char *)g_error_list[nb]);
		if (line != -1)
			ft_putnbr(line);
	}
	else
		advanced_error(data, nb, line);
	free_all(data);
	return (0);
}
