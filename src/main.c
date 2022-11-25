/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:17:05 by frafal            #+#    #+#             */
/*   Updated: 2022/11/22 14:55:35 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, t_pt pt)
{
	char	*pixel;
	int		x;
	int		y;

	x = round(pt.x);
	y = round(pt.y);

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	pixel = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(int *)pixel = pt.color;
}

t_map	*generate_map(t_data *data)
{
	t_pt	*cur;
	t_map	*map;
	t_pt	pt;
	int		i;
	int		j;
	t_pt	ground;
	t_pt	max;
	t_pt	min;

	map = data->map;
	map->min_height = 0;
	map->max_height = 0;
	map->pt_arr = malloc(map->x_dim * map->y_dim * sizeof(t_pt));
	if (map->pt_arr == NULL)
		return (NULL);
	map->space = 1;
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
			if (cur->z < map->min_height)
				map->min_height = cur->z;
			if (cur->z > map->max_height)
				map->max_height = cur->z;
			cur->color = GROUND_COLOR;
			pt.x += map->space;
			j++;
		}
		pt.y += map->space;
		i++;
	}
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
	return (map);
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

void	draw_map(t_img *img, t_map *map, t_pt offset)
{
	int		i;
	t_pt	pt;
	t_pt	neighbour_right;
	t_pt	neighbour_down;
	t_pt	*cur;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		cur = map->pt_arr + i;
		pt = vec_add(*cur, offset);
		if (i % map->x_dim != map->x_dim - 1)
		{
			neighbour_right = vec_add(*(cur + 1), offset);
			draw_line(img, pt, neighbour_right);
		}
		if (i < map->x_dim * map->y_dim - map->x_dim)
		{
			neighbour_down = vec_add(*(cur + map->x_dim), offset);
			draw_line(img, pt, neighbour_down);
		}
		i++;
	}
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			img_pix_put(img, (t_pt){j, i, 0, color});
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf MAPFILE\n", 2);
		return (-1);
	}
	if (parse_file(&data, argv[1]) == -1)
		return (-1);
	generate_map(&data);
	generate_iso_view(data.map);
	if (start_mlx(&data) == -1)
		return (-1);
	return (0);
}
