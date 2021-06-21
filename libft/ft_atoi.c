/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:15:49 by agirona           #+#    #+#             */
/*   Updated: 2021/06/17 14:20:47 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	conv(const char *str, int i, int neg)
{
	long int		tmp;
	int				res;

	tmp = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		if (res < tmp && neg == -1)
			return (0);
		else if (res < tmp)
			return (-1);
		tmp = res;
		i++;
	}
	return (res * neg);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				neg;

	i = 0;
	while (str[i] == '\r' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\t' || str[i] == '\f' || str[i] == ' ')
		i++;
	neg = 1;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	return (conv(str, i, neg));
}
