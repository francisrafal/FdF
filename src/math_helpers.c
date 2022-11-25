/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:54 by frafal            #+#    #+#             */
/*   Updated: 2022/11/25 12:50:58 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pt	mat_mult(t_matrix3x3 mat, t_pt pt)
{
	t_pt	res;

    res.x = pt.x * mat.c1r1 + pt.y * mat.c2r1 + pt.z * mat.c3r1;
    res.y = pt.x * mat.c1r2 + pt.y * mat.c2r2 + pt.z * mat.c3r2;
    res.z = pt.x * mat.c1r3 + pt.y * mat.c2r3 + pt.z * mat.c3r3;
    res.color = pt.color;
	return (res);
}