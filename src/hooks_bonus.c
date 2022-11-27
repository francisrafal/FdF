/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:06:12 by frafal            #+#    #+#             */
/*   Updated: 2022/11/25 12:06:14 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int	loop_hook(t_data *data)
{
	t_map	*map;
	t_pt	offset;

	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, DGREY);
	map = data->map;
	offset.x = WIN_W / 2;
	offset.y = WIN_H / 2;
	offset.z = 0;
	if (data->animate_on)
		rotate_y(data->map, -0.01);
	draw_map(&data->img, map, offset);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	render_instructions(data, WHITE);
	return (0);
}

int	key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (keysym == XK_equal)
		zoom(data->map, 1.2);
	if (keysym == XK_minus)
		zoom(data->map, 1/1.2);
	if (keysym == XK_Left)
		translate(data->map, (t_pt){-10, 0, 0, 0});
	if (keysym == XK_Right)
		translate(data->map, (t_pt){10, 0, 0, 0});
	if (keysym == XK_Up)
		translate(data->map, (t_pt){0, -10, 0, 0});
	if (keysym == XK_Down)
		translate(data->map, (t_pt){0, 10, 0, 0});
	if (keysym == XK_w)
		rotate_x(data->map, -0.1);
	if (keysym == XK_s)
		rotate_x(data->map, 0.1);
	if (keysym == XK_d)
		rotate_y(data->map, -0.1);
	if (keysym == XK_a)
		rotate_y(data->map, 0.1);
	if (keysym == XK_space)
		data->animate_on ^= 0x1;
	return (0);
}

int	close_app(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

int	start_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_putstr_fd("Failed to set up the connection to the X server\n", 2);
	if (data->mlx_ptr == NULL)
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, "FdF");
	if (data->win_ptr == NULL)
		ft_putstr_fd("Failed to create a new window\n", 2);
	if (data->win_ptr == NULL)
		return (-1);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	mlx_loop_hook(data->mlx_ptr, loop_hook, data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, close_app, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->map->pt_arr);
	free(data->map);
	free(data->mlx_ptr);
	free_str_arr(data->parsed_file);
	return (0);
}
