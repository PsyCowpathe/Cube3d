/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 19:09:50 by agirona           #+#    #+#             */
/*   Updated: 2021/06/06 19:32:00 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		error(t_mlx *data, int nb, int line)
{
	ft_putstr("Error\n");
	if (nb == 1)
		ft_putstr("Error empty line at start of file.");
	if (nb == 2)
	{
		ft_putstr("Space at start of line : ");
		ft_putnbr(line);
	}
	if (nb == 3)
	{
		ft_putstr("Space at end of line : ");
		ft_putnbr(line);
	}
	if (nb == 4)
		ft_putstr("Empty line at end of file.");
	if (nb == 5)
	{
		ft_putstr("Empty line in map at line : ");
		ft_putnbr(line);
	}
	if (nb == 6)
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
	if (nb == 7)
	{
		ft_putstr("Incorrect information at line : ");
		ft_putnbr(line);
	}
	if (nb == 8)
	{
		if (nb == 0)
			ft_putstr("Invalid caractere in floor color.");
		else
			ft_putstr("Invalid caractere in ceiling color.");
	}
	if (nb == 9)
		ft_putstr("Color of floor and ceiling must be between 0 and 255.");
	if (nb == 10 && line == 0)
		ft_putstr("Missing space after 'F' in floor color.");
	else if (nb == 10)
		ft_putstr("Missing space after 'C' in ceiling color.");
	if (nb == 11)
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
	if (nb == 12)
		ft_putstr("Malloc allocation failed");
	if (nb == 13)
		ft_putstr("Sorry but this game doesnt support multiplayer =)\nPlease set only one spawn point.");
	if (nb == 14)
		ft_putstr("Map isnt closed !");
	if (nb == 15)
		ft_putstr("Game cant start without you ;)\nPlease set a spawn point.");
	return (0);
}
