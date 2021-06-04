/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:26:02 by agirona           #+#    #+#             */
/*   Updated: 2020/12/04 00:46:52 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isch(const char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

static char		*ft_cut(char const *str, int start, int len)
{
	char	*res;
	int		i;

	i = 0;
	if ((res = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = str[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char		*ft_new(char *res, size_t size)
{
	if ((res = malloc(sizeof(char) * size)) == NULL)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	char	*res;

	i = 0;
	res = NULL;
	if (!s1)
		return (NULL);
	while (ft_isch(set, s1[i]))
		i++;
	start = i;
	if (s1[start] == '\0')
		return (ft_new(res, 1));
	i = ft_strlen(s1);
	while (ft_isch(set, s1[i - 1]))
		i--;
	if (i == 0)
		return (ft_new(res, 1));
	return (ft_cut(s1, start, i - start));
}
