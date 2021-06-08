/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:36:12 by agirona           #+#    #+#             */
/*   Updated: 2021/03/12 17:43:50 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		len;
	int		neg;
	long	nbr;
	char	*res;

	len = 1;
	nbr = n;
	while (nbr /= 10)
		len++;
	neg = (n < 0) ? 1 : 0;
	nbr = n;
	nbr = (nbr < 0) ? nbr * -1 : nbr;
	if ((res = malloc(sizeof(char) * len + neg + 1)) == NULL)
		return (NULL);
	res[0] = (neg == 1) ? '-' : '0';
	res[len + neg--] = '\0';
	while (len != 0)
	{
		res[len + neg] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	return (res);
}
