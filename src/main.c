/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:17:05 by frafal            #+#    #+#             */
/*   Updated: 2022/11/22 13:57:57 by frafal           ###   ########.fr       */
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

void	draw_grid(t_img *img)
{
	int x_dim = 100;
	int y_dim = 100;
	t_pt	*map = malloc(x_dim * y_dim * sizeof(t_pt));
	int	i;
	int j;
	int	x;
	int	y;
	int	z;
	int space;
	(void)img;

	z = 0;
	space = 5;
	y = 0;
	i = 0;
	while (i < y_dim)
	{
		x = 0;
		j = 0;
		while (j < x_dim)
		{	
			(map + i * y_dim + j)->x = x;
			(map + i * y_dim + j)->y = y;
			(map + i * y_dim + j)->z = z;
			x += space;
			z += 1000;
			j++;
		}
		y += space;
		i++;
	}

	i = 0;
	while (i < x_dim * y_dim)
	{
		x = (map + i)->x + WIN_W / 2 - space * x_dim / 2;
		y = (map + i)->y + WIN_H / 2 - space * y_dim / 2;
		img_pix_put(img, x, y, (map + i)->z);
		i++;
	}
	free(map);
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
	if (data->win_ptr == NULL)
		return (1);
	//render_background(&data->img, BLACK);
	//draw_vline(&data->img, WIN_W / 2, WHITE);
	//draw_circle(&data->img, WHITE);
	//draw_rect(&data->img,
	//		(t_rect){0, WIN_H / 4, WIN_W / 10, WIN_H / 2, WHITE});
	//draw_rect(&data->img,
	//		(t_rect){WIN_W / 10 * 9, WIN_H / 4, WIN_W / 10, WIN_H / 2, WHITE});
	draw_grid(&data->img);
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
	free(data.mlx_ptr);
	return (0);
}
