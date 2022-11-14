/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:17:05 by frafal            #+#    #+#             */
/*   Updated: 2022/11/14 17:04:29 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	void *mlx;
	void *mlx_win;
	void *img;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		ft_putstr_fd("Failed to set up the connection to the X server\n", 2);
		return (-1);
	}
	img = mlx_new_image(mlx, 1920, 1080);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FdF");
	if (mlx_win == NULL)
	{
		ft_putstr_fd("Failed to create a new window\n", 2);
		return (-1);
	}
//	mlx_loop(mlx);
	return (0);
}
