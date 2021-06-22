/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 19:09:50 by agirona           #+#    #+#             */
/*   Updated: 2021/06/21 20:07:18 by agirona          ###   ########lyon.fr   */
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
