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
	rotate_x(map, -M_PI_2);
	rotate_y(map, M_PI_4);
	rotate_x(map, ISO);
}

void	scale_z(t_data *data, float_t factor)
{
	t_matrix3x3	scale_z;
	t_matrix3x3	tmp;
	t_map		*map;

	map = data->map;
	tmp = (t_matrix3x3){map->base_i.x, map->base_i.y, map->base_i.z,
		map->base_j.x, map->base_j.y, map->base_j.z,
		map->base_k.x, map->base_k.y, map->base_k.z};
	scale_z = (t_matrix3x3){1, 0, 0, 0, 1, 0, 0, 0, factor};
	restore_map(data);
	transform_map(map, scale_z);
	transform_map(map, tmp);
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
	map->base_i = mat_mult(mat, map->base_i);
	map->base_j = mat_mult(mat, map->base_j);
	map->base_k = mat_mult(mat, map->base_k);
	return (map);
}
