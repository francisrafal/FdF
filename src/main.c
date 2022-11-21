/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:17:05 by frafal            #+#    #+#             */
/*   Updated: 2022/11/21 11:54:08 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include <math.h>

//REMOVE BEFORE SUBMISSION
#include <stdio.h>

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

int	key_hook(int keycode, void *param)
{
	(void)keycode;
	void	*mlx_ptr;
	void	*win_ptr;

	// CAREFUL HERE, COULD NOT WORK WITH DIFFERENT WINDOW SIZES!!!!!!!!
	// FIND A DIFFERENT SOLUTION LATER
	mlx_ptr = param;
	win_ptr = param + 9984;
	mlx_string_put(mlx_ptr, win_ptr, 50, 50, 0x00FF0000, "Let's get the games started!");
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	void	*mlx_ptr;
	void	*win_ptr;
	int		green;

	green = 0x0000FF00; 
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
	{
		ft_putstr_fd("Failed to set up the connection to the X server\n", 2);
		return (-1);
	}
	win_ptr = mlx_new_window(mlx_ptr, 1280, 720, "FdF");
	if (win_ptr == NULL)
	{
		ft_putstr_fd("Failed to create a new window\n", 2);
		return (-1);
	}
	ft_printf("mlx_ptr: %p\n", mlx_ptr);
	ft_printf("win_ptr: %p\n", win_ptr);
	ft_printf("win_ptr - mlx_ptr: %d\n", win_ptr - mlx_ptr);
	draw_vline(mlx_ptr, win_ptr, 640, green);
	draw_circle(mlx_ptr, win_ptr, green);
	mlx_key_hook(win_ptr, key_hook, mlx_ptr);
	mlx_loop(mlx_ptr);
	return (0);
}
