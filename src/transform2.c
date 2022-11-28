/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:53:42 by frafal            #+#    #+#             */
/*   Updated: 2022/11/27 09:53:42 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_map *map, float_t angle)
{
	t_matrix3x3	rot_x;

	rot_x = (t_matrix3x3){
		1, 0, 0,
		0, cos(angle), -sin(angle),
		0, sin(angle), cos(angle)};
	transform_map(map, rot_x);
}

void	rotate_y(t_map *map, float_t angle)
{
	t_matrix3x3	rot_y;

	rot_y = (t_matrix3x3){
		cos(angle), 0, sin(angle),
		0, 1, 0,
		-sin(angle), 0, cos(angle)};
	transform_map(map, rot_y);
}

void	set_xy_min_max(t_map *map)
{
	t_pt	*cur;
	int		i;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		cur = map->pt_arr + i;
		if (cur->x < map->min_x)
			map->min_x = cur->x;
		if (cur->x > map->max_x)
			map->max_x = cur->x;
		if (cur->y < map->min_y)
			map->min_y = cur->y;
		if (cur->y > map->max_y)
			map->max_y = cur->y;
		i++;
	}
}

void	autoscale(t_map *map)
{
	float_t	scale_x;
	float_t	scale_y;

	map->min_x = 0;
	map->max_x = 0;
	map->min_y = 0;
	map->max_y = 0;
	set_xy_min_max(map);
	scale_x = (WIN_W / 2 - 30) / fmaxf(abs(map->max_x), abs(map->min_x));
	scale_y = (WIN_H / 2 - 30) / fmaxf(abs(map->max_y), abs(map->min_y));
	zoom(map, fminf(scale_x, scale_y));
}

void	restore_map(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->map->x_dim * data->map->y_dim)
	{
		*(data->map->pt_arr + i) = *(data->original_map->pt_arr + i);
		i++;
	}
	data->map->base_i = (t_pt){1, 0, 0, 0x0};
	data->map->base_j = (t_pt){0, 1, 0, 0x0};
	data->map->base_k = (t_pt){0, 0, 1, 0x0};
}
