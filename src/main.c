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

	if (x < 0 || y < 0)
		return ;
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
	pt.z = 0;
	pt.y = 0;
	i = 0;
	while (i < map->y_dim)
	{
		pt.x = 0;
		j = 0;
		while (j < map->x_dim)
		{	
			cur = map->pt_arr + i * map->x_dim + j;
			*cur = pt;
			if (j == map->x_dim / 2 || j == 0 || j == map->x_dim - 1)
				cur->z = 10;
			pt.x += map->space;
			j++;
		}
		pt.y += map->space;
		i++;
	}
	return (map);
}

t_map	*transform_map(t_map *map, t_matrix3x3 mat)
{

	int		i;
	t_pt	pt;
	t_pt	*cur;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		cur = map->pt_arr + i;
		pt = *cur;
		cur->x = pt.x * mat.c1r1 + pt.y * mat.c2r1 + pt.z * mat.c3r1;
		cur->y = pt.x * mat.c1r2 + pt.y * mat.c2r2 + pt.z * mat.c3r2;
		cur->z = pt.x * mat.c1r3 + pt.y * mat.c2r3 + pt.z * mat.c3r3;
		i++;
	}
	return (map);
}

int	draw_line_low(t_img *img, t_pt start, t_pt end, int color)
{
	int dx;
	int dy;
	int err;
	int yi;

	dx = end.x - start.x;
	dy = end.y - start.y;
	yi = 1;
	if (dy < 0)
		{
			yi = -1;
			dy = -dy;
		}
	err = 2 * dy - dx;
	while (start.x < end.x)
	{
		img_pix_put(img, start.x, start.y, color);
		if (err > 0)
			{
				start.y += yi;
				err = err + (2 * (dy - dx));
			}
		else
			err = err + 2 * dy;
		start.x++;
	}
	return (0);
}

int	draw_line_high(t_img *img, t_pt start, t_pt end, int color)
{
	int dx;
	int dy;
	int err;
	int xi;

	dx = end.x - start.x;
	dy = end.y - start.y;
	xi = 1;
	if (dx < 0)
		{
			xi = -1;
			dx = -dx;
		}
	err = 2 * dx - dy;
	while (start.y < end.y)
	{
		img_pix_put(img, start.x, start.y, color);
		if (err > 0)
			{
				start.x += xi;
				err = err + (2 * (dx - dy));
			}
		else
			err = err + 2 * dx;
		start.y++;
	}
	return (0);
}

int	draw_line(t_img *img, t_pt start, t_pt end, int color)
{
	if (fabsf(end.y - start.y) < fabsf(end.x - start.x))
	{
		if (start.x > end.x)
			return(draw_line_low(img, end, start, color));
		return(draw_line_low(img, start, end, color));
	}
	if (start.y > end.y)
		return(draw_line_high(img, end, start, color));
	return(draw_line_high(img, start, end, color));
	return (-1);
}

void	draw_map(t_img *img, t_map *map, t_pt offset)
{
	int		i;
	t_pt	pt;
	t_pt	neighbour_right;
	t_pt	neighbour_down;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		pt.x = (map->pt_arr + i)->x + offset.x;
		pt.y = (map->pt_arr + i)->y + offset.y;
		pt.z = (map->pt_arr + i)->z + offset.z;
		if (i % map->x_dim != map->x_dim - 1)
		{
			neighbour_right.x = (map->pt_arr + i + 1)->x + offset.x;
			neighbour_right.y = (map->pt_arr + i + 1)->y + offset.y;
			neighbour_right.z = (map->pt_arr + i + 1)->z + offset.z;
			draw_line(img, pt, neighbour_right, WHITE);
		}
		if (i / map->y_dim != map->y_dim - 1)
		{
			neighbour_down.x = (map->pt_arr + i + map->x_dim)->x + offset.x;
			neighbour_down.y = (map->pt_arr + i + map->x_dim)->y + offset.y;
			neighbour_down.z = (map->pt_arr + i + map->x_dim)->z + offset.z;
			draw_line(img, pt, neighbour_down, WHITE);
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
			img_pix_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

int	loop_hook(t_data *data)
{
	t_map	*map;
	t_pt	offset;

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
	offset.x = 0;
	offset.y = 0;
	offset.x = WIN_W / 2 - map->space * map->x_dim / 2;
	offset.y = WIN_H / 2 - map->space * map->y_dim / 2;
	offset.z = 0;
	draw_map(&data->img, map, offset);
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
	t_data	data;
	int		fd;
	char	*line;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf MAPFILE\n", 2);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Failed to open file\n", 2);
		return (-1);
	}
	line = "";
	// COUNT LINES
	// COUNT NUMBERS
	// split line into char **arr
	// add all lines to char ***arr | NULL TERMINATED
	// generate_map with z = atoi
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			ft_printf("%s", line);
			free(line);
			line = "";
		}
	}
	if (close(fd) == - 1)
	{
		ft_putstr_fd("Failed to close file\n", 2);
		return (-1);
	}
	// PARSE FILE TO ARR
	t_matrix3x3 rot_x_90;
	t_matrix3x3 rot_z_45;
	t_matrix3x3 rot_x_iso;
	
	rot_x_90 = (t_matrix3x3){1, 0, 0, 0, 0, 1, 0, -1, 0};
	rot_z_45 = (t_matrix3x3){cos(M_PI_4), 0, sin(M_PI_4), 0, 1, 0, -sin(M_PI_4), 0, cos(M_PI_4)};
	rot_x_iso = (t_matrix3x3){1, 0, 0, 0, cos(ISO), -sin(ISO), 0, sin(ISO), cos(ISO)};
	data.map = generate_map();
	data.map = transform_map(data.map, rot_x_90);
	data.map = transform_map(data.map, rot_z_45);
	data.map = transform_map(data.map, rot_x_iso);
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
