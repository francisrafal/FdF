/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:17:05 by frafal            #+#    #+#             */
/*   Updated: 2022/11/21 17:04:41 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_circle(t_data *data, int color)
{
	double_t	phi;

	phi = 0;
	while (phi < 2 * M_PI)
	{
		int x = round(WIN_WIDTH / 10 * cos(phi) + WIN_WIDTH / 2);
		int y = round(WIN_WIDTH / 10 * sin(phi) + WIN_HEIGHT / 2);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		phi += 0.001;
	}
}

void	draw_vline(t_data *data, int x, int color)
{
	int i;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, i, color);
		i++;
	}
}

void	draw_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			if (i == rect.y || i == rect.y + rect.height - 1 || j == rect.x || j == rect.x + rect.width - 1)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, j, i, rect.color);
			j++;
		}
		i++;
	}
}

int	loop_hook(t_data *data)
{
	if (data->win_ptr != NULL)
	{
		draw_vline(data, WIN_WIDTH / 2, GREEN);
		draw_circle(data, GREEN);
		draw_rect(data, (t_rect){0, WIN_HEIGHT / 4, WIN_WIDTH / 10, WIN_HEIGHT / 2, GREEN});
		draw_rect(data, (t_rect){WIN_WIDTH / 10 * 9, WIN_HEIGHT / 4, WIN_WIDTH / 10, WIN_HEIGHT / 2, GREEN});
	}
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
	mlx_loop_hook(data->mlx_ptr, loop_hook, data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data);
	return (0);
}
