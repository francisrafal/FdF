/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:09:34 by frafal            #+#    #+#             */
/*   Updated: 2022/11/25 12:09:39 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float_t	get_percentage(int start, int end, int cur)
{
	float_t	position;
	float_t	delta;

	delta = end - start;
	if (delta == 0)
		return (1.0);
	position = cur - start;
	return (position / delta);
}

int	calc_color_channel(int start, int end, float_t percentage)
{
	int	color_channel;

	color_channel = (1 - percentage) * start + percentage * end;
	return (color_channel);
}

int	get_color(t_pt cur, t_pt start, t_pt end, t_pt delta)
{
	int		red;
	int		green;
	int		blue;
	float_t	percentage;

	if (cur.color == end.color)
		return (cur.color);
	if (delta.x > delta.y)
		percentage = get_percentage(start.x, end.x, cur.x);
	else
		percentage = get_percentage(start.y, end.y, cur.y);
	red = calc_color_channel((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, percentage);
	green = calc_color_channel((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, percentage);
	blue = calc_color_channel(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int	get_height_gradient_color(t_pt cur, t_pt start, t_pt end)
{
	int		red;
	int		green;
	int		blue;
	float_t	percentage;

	percentage = get_percentage(fabsf(start.z), fabsf(end.z), fabsf(cur.z));
	red = calc_color_channel((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, percentage);
	green = calc_color_channel((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, percentage);
	blue = calc_color_channel(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
