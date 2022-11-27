/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:23:42 by frafal            #+#    #+#             */
/*   Updated: 2022/11/25 13:23:53 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	generate_iso_view(t_map *map)
{
	t_matrix3x3	rot_x_90;
	t_matrix3x3	rot_z_45;
	t_matrix3x3	rot_x_iso;

	rot_x_90 = (t_matrix3x3){1, 0, 0, 0, 0, 1, 0, -1, 0};
	rot_z_45 = (t_matrix3x3){
		cos(M_PI_4), 0, sin(M_PI_4),
		0, 1, 0,
		-sin(M_PI_4), 0, cos(M_PI_4)};
	rot_x_iso = (t_matrix3x3){
		1, 0, 0,
		0, cos(ISO), -sin(ISO),
		0, sin(ISO), cos(ISO)};
	transform_map(map, rot_x_90);
	transform_map(map, rot_z_45);
	transform_map(map, rot_x_iso);
}

void	scale_z(t_map *map)
{
	t_matrix3x3	scale_z_1_2;

	scale_z_1_2 = (t_matrix3x3){1, 0, 0, 0, 1, 0, 0, 0, 0.5};
	transform_map(map, scale_z_1_2);
}

void	zoom(t_map *map, float_t factor)
{
	t_matrix3x3	scale;

	scale = (t_matrix3x3){factor, 0, 0, 0, factor, 0, 0, 0, factor};
	transform_map(map, scale);
}

void	translate(t_map *map, t_pt offset)
{
	int		i;
	t_pt	*cur;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		cur = map->pt_arr + i;
		*cur = vec_add(*cur, offset);
		i++;
	}
}

t_map	*transform_map(t_map *map, t_matrix3x3 mat)
{
	int		i;
	t_pt	*cur;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		cur = map->pt_arr + i;
		*cur = mat_mult(mat, *cur);
		i++;
	}
	return (map);
}
