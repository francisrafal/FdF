/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:53:42 by frafal            #+#    #+#             */
/*   Updated: 2022/11/27 09:53:42 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    rotate_x(t_map *map, float_t angle)
{
	t_matrix3x3	rot_x;

	rot_x = (t_matrix3x3){
		1, 0, 0,
		0, cos(angle), -sin(angle),
		0, sin(angle), cos(angle)};
	transform_map(map, rot_x);
}

void    rotate_y(t_map *map, float_t angle)
{
	t_matrix3x3	rot_y;

	rot_y = (t_matrix3x3){
		cos(angle), 0, sin(angle),
		0, 1, 0,
		-sin(angle), 0, cos(angle)};
	transform_map(map, rot_y);
}