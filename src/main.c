/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:17:05 by frafal            #+#    #+#             */
/*   Updated: 2022/11/21 14:36:59 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_circle(void *mlx_ptr, void *win_ptr, int color)
{
	double_t	phi;

	phi = 0;
	while (phi < 2 * M_PI)
	{
		int x = round(100*cos(phi) + 640);
		int y = round(100*sin(phi) + 360);
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
		phi += 0.01;
	}
}

void	draw_vline(void *mlx_ptr, void *win_ptr, int x, int color)
{
	int i;

	i = 0;
	while (i < 720)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, i, color);
		i++;
	}
}

int	key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free(data);
		exit(0);
	}
	//ft_putnbr_fd(keycode, 1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data	*data;

	// READ FILE
	// PARSE FILE TO ARR
	// TESTARR
	// TRANSFORM MAP
	// DRAW MAP
	
	data = malloc(sizeof(t_data));
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		ft_putstr_fd("Failed to set up the connection to the X server\n", 2);
		return (-1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (data->win_ptr == NULL)
	{
		ft_putstr_fd("Failed to create a new window\n", 2);
		return (-1);
	}
	draw_vline(data->mlx_ptr, data->win_ptr, 640, GREEN);
	draw_circle(data->mlx_ptr, data->win_ptr, GREEN);
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
