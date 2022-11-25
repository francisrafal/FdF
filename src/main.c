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
	int	red;
	int	green;
	int	blue;
	float_t	percentage;

	if (cur.color == end.color)
		return (cur.color);
	if (delta.x > delta.y)
		percentage = get_percentage(start.x, end.x, cur.x);
	else
		percentage = get_percentage(start.y, end.y, cur.y);
	red = calc_color_channel((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	green = calc_color_channel((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	blue = calc_color_channel(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int	get_height_gradient_color(t_pt cur, t_pt start, t_pt end)
{
	int	red;
	int	green;
	int	blue;
	float_t	percentage;

	percentage = get_percentage(fabsf(start.z), fabsf(end.z), fabsf(cur.z));
	red = calc_color_channel((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	green = calc_color_channel((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	blue = calc_color_channel(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
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
	//ft_printf("min_height: %d\nmax_height: %d\n", map->min_height, map->max_height);
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

int	draw_line_low(t_img *img, t_pt start, t_pt end)
{
	int		err;
	int		yi;
	t_pt	delta;
	t_pt	cur;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	yi = 1;
	if (delta.y < 0)
		{
			yi = -1;
			delta.y = -delta.y;
		}
	err = 2 * delta.y - delta.x;
	cur = start;
	while (cur.x < end.x)
	{
		img_pix_put(img, cur);
		if (err > 0)
			{
				cur.y += yi;
				err = err + (2 * (delta.y - delta.x));
			}
		else
			err = err + 2 * delta.y;
		cur.color = get_color(cur, start, end, delta);
		cur.x++;
	}
	return (0);
}

int	draw_line_high(t_img *img, t_pt start, t_pt end)
{
	int		err;
	int		xi;
	t_pt	delta;
	t_pt	cur;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	xi = 1;
	if (delta.x < 0)
		{
			xi = -1;
			delta.x = -delta.x;
		}
	err = 2 * delta.x - delta.y;
	cur = start;
	while (cur.y < end.y)
	{
		img_pix_put(img, cur);
		if (err > 0)
			{
				cur.x += xi;
				err = err + (2 * (delta.x - delta.y));
			}
		else
			err = err + 2 * delta.x;
		cur.color = get_color(cur, start, end, delta);
		cur.y++;
	}
	return (0);
}

int	draw_line(t_img *img, t_pt start, t_pt end)
{
	if (fabsf(end.y - start.y) < fabsf(end.x - start.x))
	{
		if (start.x > end.x)
			return(draw_line_low(img, end, start));
		return(draw_line_low(img, start, end));
	}
	if (start.y > end.y)
		return(draw_line_high(img, end, start));
	return(draw_line_high(img, start, end));
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
		pt.color = (map->pt_arr + i)->color;
		if (i % map->x_dim != map->x_dim - 1)
		{
			neighbour_right.x = (map->pt_arr + i + 1)->x + offset.x;
			neighbour_right.y = (map->pt_arr + i + 1)->y + offset.y;
			neighbour_right.z = (map->pt_arr + i + 1)->z + offset.z;
			neighbour_right.color = (map->pt_arr + i + 1)->color;
			draw_line(img, pt, neighbour_right);
		}
		if (i < map->x_dim * map->y_dim - map->x_dim)
		{
			neighbour_down.x = (map->pt_arr + i + map->x_dim)->x + offset.x;
			neighbour_down.y = (map->pt_arr + i + map->x_dim)->y + offset.y;
			neighbour_down.z = (map->pt_arr + i + map->x_dim)->z + offset.z;
			neighbour_down.color = (map->pt_arr + i + map->x_dim)->color;
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

int	loop_hook(t_data *data)
{
	t_map	*map;
	t_pt	offset;

	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, DGREY);
	map = data->map;
	offset.x = 0;
	offset.y = 0;
	offset.x = WIN_W / 2;
	offset.y = WIN_H / 2;
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

int	close_app(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

void	replace_newline(unsigned int i, char *s)
{
	(void)i;
	if (*s == '\n')
		*s = ' ';
}

int	print_parsed_file(char **parsed_file)
{
	int	i;

	i = 0;
	while (parsed_file[i] != NULL)
	{
		ft_printf("%s\n", parsed_file[i]);
		i++;
	}
	return (i);
}

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

int		count_cols(char *s)
{
	int	cols;
	char **split;

	cols = 0;
	ft_striteri(s, replace_newline);
	split = ft_split(s, ' ');
	while (split[cols] != NULL)
		cols++;
	free_str_arr(split);
	return (cols);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	char	*line;
	char	*file;
	char	*tmp;
	int		cols;

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
	data.map = malloc(sizeof(t_map));
	if (data.map == NULL)
		return (-1);
	line = "";
	file = malloc(sizeof(char));
	file[0] = '\0';
	data.map->y_dim = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			cols = count_cols(line);
			if (data.map->y_dim != 0 && data.map->x_dim != cols)
			{
				ft_putstr_fd("Found wrong line length. Exiting.\n", 2);
				return (-1);
			}
			data.map->x_dim = cols;
			data.map->y_dim += 1;
			tmp = file;
			file = ft_strjoin(tmp, line);
			free(tmp);
			free(line);
			line = "";
		}
	}
	//ft_printf(file);
	ft_striteri(file, replace_newline);
	//ft_printf(file);
	data.parsed_file = ft_split(file, ' ');
	//ft_printf("parsed_file length: %d\n", print_parsed_file(data.parsed_file));
	//ft_printf("x_dim: %d, y_dim: %d\n", data.map->x_dim, data.map->y_dim);
	free(file);
	if (close(fd) == -1)
	{
		ft_putstr_fd("Failed to close file\n", 2);
		return (-1);
	}
	t_matrix3x3 rot_x_90;
	t_matrix3x3 rot_z_45;
	t_matrix3x3 rot_x_iso;
	t_matrix3x3 scale_10;
	t_matrix3x3 scale_2;
	t_matrix3x3 scale_30;
	t_matrix3x3 scale_z_1_2;
	
	rot_x_90 = (t_matrix3x3){1, 0, 0, 0, 0, 1, 0, -1, 0};
	rot_z_45 = (t_matrix3x3){cos(M_PI_4), 0, sin(M_PI_4), 0, 1, 0, -sin(M_PI_4), 0, cos(M_PI_4)};
	rot_x_iso = (t_matrix3x3){1, 0, 0, 0, cos(ISO), -sin(ISO), 0, sin(ISO), cos(ISO)};
	scale_10 = (t_matrix3x3){10, 0, 0, 0, 10, 0, 0, 0, 10};
	scale_30 = (t_matrix3x3){30, 0, 0, 0, 30, 0, 0, 0, 30};
	scale_2 = (t_matrix3x3){2, 0, 0, 0, 2, 0, 0, 0, 2};
	scale_z_1_2 = (t_matrix3x3){1, 0, 0, 0, 1, 0, 0, 0, 0.5};
	data.map = generate_map(&data);
	data.map = transform_map(data.map, scale_z_1_2);
	data.map = transform_map(data.map, rot_x_90);
	data.map = transform_map(data.map, rot_z_45);
	data.map = transform_map(data.map, rot_x_iso);
	//data.map = transform_map(data.map, scale_2);
	data.map = transform_map(data.map, scale_10);
	//data.map = transform_map(data.map, scale_30);
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
	mlx_hook(data.win_ptr, DestroyNotify, 0, close_app, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.map->pt_arr);
	free(data.map);
	free(data.mlx_ptr);
	free_str_arr(data.parsed_file);
	return (0);
}
