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

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(int *)pixel = color;
}

void	draw_circle(t_img *img, int color)
{
	double_t	phi;
	int			x;
	int			y;

	phi = 0;
	while (phi < 2 * M_PI)
	{
		x = round(WIN_W / 10 * cos(phi) + WIN_W / 2);
		y = round(WIN_W / 10 * sin(phi) + WIN_H / 2);
		img_pix_put(img, x, y, color);
		phi += 0.001;
	}
}

void	draw_vline(t_img *img, int x, int color)
{
	int	i;

	i = 0;
	while (i < WIN_H)
	{
		img_pix_put(img, x, i, color);
		i++;
	}
}

void	draw_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			if (i == rect.y || i == rect.y + rect.height - 1
				|| j == rect.x || j == rect.x + rect.width - 1)
				img_pix_put(img, j, i, rect.color);
			j++;
		}
		i++;
	}
}

t_map	*generate_map(void)
{
	t_map	*map;
	t_pt	*cur;
	t_pt	pt;
	int		i;
	int		j;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->x_dim = 30;
	map->y_dim = 30;
	map->pt_arr = malloc(map->x_dim * map->y_dim * sizeof(t_pt));
	if (map->pt_arr == NULL)
		return (NULL);
	map->space = 10;
	pt.z = WHITE;
	ft_printf("%d\n", pt.z);
	pt.y = 0;
	i = 0;
	while (i < map->y_dim)
	{
		pt.x = 0;
		j = 0;
		while (j < map->x_dim)
		{	
			cur = map->pt_arr + i * map->x_dim + j;
			cur->x = pt.x;
			cur->y = pt.y;
			cur->z = pt.z;
			pt.x += map->space;
			pt.z -= 10;
			ft_printf("%d\n", pt.z);
			j++;
		}
		pt.y += map->space;
		i++;
	}
	return (map);
}

t_map	*transform_map(t_map *map)
{
	t_matrix3x3	mat;

	mat.i.x = 1;
	mat.i.y = 0;
	mat.i.z = 0;
	mat.j.x = 1;
	mat.j.y = 1;
	mat.j.z = 0;
	mat.k.x = 0;
	mat.k.y = 0;
	mat.k.z = 1;

	int		i;
	t_pt	pt;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		pt.x = (map->pt_arr + i)->x;
		pt.y = (map->pt_arr + i)->y;
		pt.z = (map->pt_arr + i)->z;
		(map->pt_arr + i)->x = pt.x * mat.i.x + pt.y * mat.j.x + pt.z * mat.k.x;
		(map->pt_arr + i)->y = pt.x * mat.i.y + pt.y * mat.j.y + pt.z * mat.k.y;
		(map->pt_arr + i)->z = pt.x * mat.i.z + pt.y * mat.j.z + pt.z * mat.k.z;
		i++;
	}
	return (map);
}

void	draw_grid(t_img *img, t_map *map)
{
	int		i;
	t_pt	pt;
	t_pt	offset;

	offset.x = 0;
	offset.y = 0;
	//offset.x = WIN_W / 2 - map->space * map->x_dim / 2;
	//offset.y = WIN_H / 2 - map->space * map->y_dim / 2;
	offset.z = 0;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		pt.x = (map->pt_arr + i)->x + offset.x;
		pt.y = (map->pt_arr + i)->y + offset.y;
		pt.z = (map->pt_arr + i)->z + offset.z;
		img_pix_put(img, pt.x, pt.y, pt.z);
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
			img_pix_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

int	loop_hook(t_data *data)
{
	t_map	*map;
	if (data->win_ptr == NULL)
		return (1);
	//render_background(&data->img, BLACK);
	//draw_vline(&data->img, WIN_W / 2, WHITE);
	//draw_circle(&data->img, WHITE);
	//draw_rect(&data->img,
	//		(t_rect){0, WIN_H / 4, WIN_W / 10, WIN_H / 2, WHITE});
	//draw_rect(&data->img,
	//		(t_rect){WIN_W / 10 * 9, WIN_H / 4, WIN_W / 10, WIN_H / 2, WHITE});
	map = data->map;
	draw_grid(&data->img, map);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data	data;
	// READ FILE
	// PARSE FILE TO ARR
	// TESTARR
	// TRANSFORM MAP
	// DRAW MAP

	data.map = generate_map();
	data.map = transform_map(data.map);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		ft_putstr_fd("Failed to set up the connection to the X server\n", 2);
		return (-1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "FdF");
	if (data.win_ptr == NULL)
	{
		ft_putstr_fd("Failed to create a new window\n", 2);
		return (-1);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, loop_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.map->pt_arr);
	free(data.map);
	free(data.mlx_ptr);
	return (0);
}
