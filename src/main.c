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
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf MAPFILE\n", 2);
		return (-1);
	}
	if (parse_file(&data, argv[1]) == -1)
		return (-1);
	generate_map(&data);
	printf("%f %f %f\n%f %f %f\n %f %f %f\n", data.map->base_i.x, data.map->base_j.x,data.map->base_k.x,data.map->base_i.y,data.map->base_j.y,data.map->base_k.y,data.map->base_i.z,data.map->base_j.z,data.map->base_k.z);
	scale_z(data.map, 1);
	generate_iso_view(data.map);
	printf("%f %f %f\n%f %f %f\n %f %f %f\n", data.map->base_i.x, data.map->base_j.x,data.map->base_k.x,data.map->base_i.y,data.map->base_j.y,data.map->base_k.y,data.map->base_i.z,data.map->base_j.z,data.map->base_k.z);
	scale_z(data.map, 1);
	autoscale(data.map);
	printf("%f %f %f\n%f %f %f\n %f %f %f\n", data.map->base_i.x, data.map->base_j.x,data.map->base_k.x,data.map->base_i.y,data.map->base_j.y,data.map->base_k.y,data.map->base_i.z,data.map->base_j.z,data.map->base_k.z);
	data.animate_on = 0;
	if (start_mlx(&data) == -1)
		return (-1);
	return (0);
}
