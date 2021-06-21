/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:11:19 by agirona           #+#    #+#             */
/*   Updated: 2021/06/17 15:21:01 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		c;
	char	*res;

	i = 0;
	c = 0;
	res = NULL;
	if (!s1)
		return (NULL);
	if (new_malloc((void *)&res, sizeof(char),
			ft_strlen(s1) + ft_strlen(s2) + 1) == 0)
		return (NULL);
	while (s1[c])
		res[i++] = s1[c++];
	c = 0;
	while (s2[c])
		res[i++] = s2[c++];
	res[i] = '\0';
	return (res);
}
