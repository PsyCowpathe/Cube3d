/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:26:47 by agirona           #+#    #+#             */
/*   Updated: 2021/05/04 14:26:55 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	*rotate(float *centerxy, float *pointxy, float angle)
{
	float	*newxy;
	float	tmpx;
	float	tmpy;

	newxy = malloc(sizeof(float) * 2);
	angle = angle * -1;
	newxy[0] = pointxy[0] - centerxy[0];
	newxy[1] = pointxy[1] - centerxy[1];
	tmpx = newxy[0] * cos(angle) - newxy[1] * sin(angle);
	tmpy = newxy[0] * sin(angle) + newxy[1] * cos(angle);
	newxy[0] = tmpx + centerxy[0];
	newxy[1] = tmpy + centerxy[1];
	return (newxy);
}
