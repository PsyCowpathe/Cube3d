/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 19:09:50 by agirona           #+#    #+#             */
/*   Updated: 2021/06/13 19:10:06 by agirona          ###   ########lyon.fr   */
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
		\nTips : Color must be between 0 and 255 in this format XXX, XXX,XXX.",
	"Color of ceiling isnt correctly formated. \
		\nTips : Color must be between 0 and 255 in this format XXX,XXX, XXX.",
	"Missing map at bottom of the file.",
	"Malloc allocation failed",
	"Empty line in map at line : ",
	"Invalid characters in map at line : ",
	"Sorry but this game doesnt support multiplayer =) \
		\nPlease set only one spawn point.",
	"Game cant start without you ;)\nPlease set a spawn point.",
	"Map isnt closed !",
	"Mlx failed to create window.",
	"Mlx failed to create principal image.",
};

void	last_error(t_mlx *data, int nb, int line)
{
	if (nb == 18)
	{
		if (data->no == 0)
			ft_putstr("Missing north texture path.\n");
		if (data->so == 0)
			ft_putstr("Missing south texture path.\n");
		if (data->ea == 0)
			ft_putstr("Missing east texture path.\n");
		if (data->we == 0)
			ft_putstr("Missing west texture path.\n");
		if (data->f == 0)
			ft_putstr("Missing floor color.\n");
		if (data->c == 0)
			ft_putstr("Missing ceiling color.\n");
		ft_putstr("Tips : Map need to be at bottom of the file\n");
	}
	if (nb == 19)
	{
		if (line == 0)
			ft_putstr("Mlx cant open north texture.");
		if (line == 1)
			ft_putstr("Mlx cant open south texture.");
		if (line == 2)
			ft_putstr("Mlx cant open east texture.");
		if (line == 3)
			ft_putstr("Mlx cant open west texture.");
		if (line == 4)
			ft_putstr("Mlx cant open sprite texture.");
		if (line == 5)
			ft_putstr("Mlx cant open sky texture.");
		if (line == 6)
			ft_putstr("Mlx cant open hand texture.");
		if (line == 7)
			ft_putstr("Mlx cant open reverse sprite texture.");
		ft_putstr("\nPlease verify if the path is correct");
		ft_putstr(" and that the image is an XPM extension.\n");
	}
}

void	advanced_error2(t_mlx *data, int nb, int line)
{
	if (nb == 17)
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
		last_error(data, nb, line);
}

void	advanced_error(t_mlx *data, int nb, int line)
{
	if (nb == 16)
	{
		if (line == 0)
			ft_putstr("Invalid characters in north declaration.\n");
		else if (line == 1)
			ft_putstr("Invalid characters in south declaration.\n");
		else if (line == 2)
			ft_putstr("Invalid characters in east declaration.\n");
		else if (line == 3)
			ft_putstr("Invalid characters in west declaration.\n");
		else if (line == 4)
			ft_putstr("Invalid characters in floor declaration.\n");
		else if (line == 5)
			ft_putstr("Invalid characters in ceiling declaration.\n");
	}
	else
		advanced_error2(data, nb, line);
}

int	error(t_mlx *data, int nb, int line, int print)
{
	if (print == 1)
		ft_putstr("Error\n");
	if (nb >= 1 && nb <= 15)
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
