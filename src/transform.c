/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:23:42 by frafal            #+#    #+#             */
/*   Updated: 2022/11/25 13:23:53 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    generate_iso_view(t_map *map)
{
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
	transform_map(map, scale_z_1_2);
	transform_map(map, rot_x_90);
	transform_map(map, rot_z_45);
	transform_map(map, rot_x_iso);
	//transform_map(map, scale_2);
	transform_map(map, scale_10);
	//transform_map(map, scale_30);
}