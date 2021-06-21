/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 04:49:02 by agirona           #+#    #+#             */
/*   Updated: 2021/06/17 14:31:10 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_hex(unsigned char nb)
{
	int				tab[2];

	tab[1] = nb % 16;
	tab[0] = nb / 16;
	ft_putchar(92);
	if (tab[0] >= 10)
		ft_putchar(97 + tab[0] - 10);
	else
		ft_putchar(tab[0] + 48);
	if (tab[1] >= 10)
		ft_putchar(97 + tab[1] - 10);
	else
		ft_putchar(tab[1] + 48);
}

void	ft_putstr_non_printable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 0 && str[i] <= 31) || str[i] >= 127 || str[i] < 0)
			print_hex(str[i]);
		else
			ft_putchar(str[i]);
		i++;
	}
}
