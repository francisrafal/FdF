/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:42:55 by frafal            #+#    #+#             */
/*   Updated: 2022/11/25 14:43:01 by frafal           ###   ########.fr       */
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

void	render_instructions(t_data *data, int color)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 30,
		color, "Zoom: Keypad +, -");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 50,
		color, "Translate: Up, Down, Left, Right");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 70,
		color, "Rotate: W, A, S, D");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 90,
		color, "Change Height: J, K");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 110,
		color, "Reset Isometric View: R");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 130,
		color, "Top View: T");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 150,
		color, "Animate: Space");
}
