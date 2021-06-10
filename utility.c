/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:26:47 by agirona           #+#    #+#             */
/*   Updated: 2021/06/10 20:49:33 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

float	angle_range(float angle)
{
	if (angle > 360)
		angle = 0 + (angle - 360);
	if (angle < 0)
		angle = 360 + angle;
	return (angle);
}

float	get_direction(t_mlx *data)
{
	float	direction;

	direction = 0;
	if (data->forward == 1)
	{
		direction = data->looking;
		if (data->forward == 1 && data->right == 1)
			direction = data->looking - 45;
		else if (data->forward == 1 && data->left == 1)
			direction = data->looking + 45;
	}
	else if (data->backward == 1)
	{
		direction = data->looking - 180;
		if (data->backward == 1 && data->right == 1)
			direction = data->looking - 180 + 45;
		else if (data->backward == 1 && data->left == 1)
			direction = data->looking - 180 - 45;
	}
	else if (data->right == 1)
		direction = data->looking - 90;
	else if (data->left == 1)
		direction = data->looking + 90;
	return (direction * (M_PI / 180));
}

int	shading(float dist, unsigned int rgb)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	float			intensity;

	intensity = 1 / dist * 4;
	if (intensity > 1)
		intensity = 1;
	r = rgb & (0xFF << 16);
	g = rgb & (0xFF << 8);
	b = rgb & 0xFF;
	r = (int)(r * intensity) & (0xFF << 16);
	g = (int)(g * intensity) & (0xFF << 8);
	b = (int)(b * intensity) & 0xFF;
	return (r | g | b);
}

float	*rotate(float *centerxy, float *pointxy, float angle)
{
	float	*newxy;
	float	tmpx;
	float	tmpy;

	newxy = malloc(sizeof(float) * 2);
	if (newxy == NULL)
		return (NULL);
	angle = angle * -1;
	newxy[0] = pointxy[0] - centerxy[0];
	newxy[1] = pointxy[1] - centerxy[1];
	tmpx = newxy[0] * cos(angle) - newxy[1] * sin(angle);
	tmpy = newxy[0] * sin(angle) + newxy[1] * cos(angle);
	newxy[0] = tmpx + centerxy[0];
	newxy[1] = tmpy + centerxy[1];
	return (newxy);
}
