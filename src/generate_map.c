/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:43:13 by frafal            #+#    #+#             */
/*   Updated: 2022/11/25 14:43:19 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*generate_map(t_data *data)
{
	t_map	*map;

	map = data->map;
	map->min_height = 0;
	map->max_height = 0;
	map->base_i = (t_pt){1, 0, 0, 0x0};
	map->base_j = (t_pt){0, 1, 0, 0x0};
	map->base_k = (t_pt){0, 0, 1, 0x0};
	map->pt_arr = malloc(map->x_dim * map->y_dim * sizeof(t_pt));
	if (map->pt_arr == NULL)
		return (NULL);
	map->space = 10;
	fill_map(data, map);
	set_point_colors(map);
	save_original_map(data);
	return (map);
}

t_map	*save_original_map(t_data *data)
{
	t_pt	*cur;
	int		i;

	data->original_map = malloc(sizeof(t_map));
	if (data->original_map == NULL)
		return (NULL);
	data->original_map->pt_arr = malloc(data->map->x_dim
			* data->map->y_dim * sizeof(t_pt));
	if (data->original_map->pt_arr == NULL)
		return (NULL);
	i = 0;
	while (i < data->map->x_dim * data->map->y_dim)
	{
		cur = data->map->pt_arr + i;
		*(data->original_map->pt_arr + i) = *cur;
		i++;
	}
	return (data->original_map);
}

void	fill_map(t_data *data, t_map *map)
{
	int		i;
	int		j;
	t_pt	*cur;
	t_pt	pt;

	pt.z = 0;
	pt.y = -map->space * map->y_dim / 2;
	i = 0;
	while (i < map->y_dim)
	{
		pt.x = -map->space * map->x_dim / 2;
		j = 0;
		while (j < map->x_dim)
		{	
			cur = map->pt_arr + i * map->x_dim + j;
			*cur = pt;
			cur->z = ft_atoi(data->parsed_file[i * map->x_dim + j]);
			set_height_range(map, cur);
			cur->color = GROUND_COLOR;
			pt.x += map->space;
			j++;
		}
		pt.y += map->space;
		i++;
	}
}

void	set_height_range(t_map *map, t_pt *cur)
{
	if (cur->z < map->min_height)
		map->min_height = cur->z;
	if (cur->z > map->max_height)
		map->max_height = cur->z;
}

void	set_point_colors(t_map *map)
{
	t_pt	ground;
	t_pt	max;
	t_pt	min;
	t_pt	*cur;
	int		i;

	ground = (t_pt){0, 0, 0, GROUND_COLOR};
	max = (t_pt){0, 0, map->max_height, HIGH_COLOR};
	min = (t_pt){0, 0, map->min_height, LOW_COLOR};
	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		cur = map->pt_arr + i;
		if (cur->z > 0)
			cur->color = get_height_gradient_color(*cur, ground, max);
		if (cur->z < 0)
			cur->color = get_height_gradient_color(*cur, ground, min);
		i++;
	}
}
