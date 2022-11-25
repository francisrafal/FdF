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

t_pt	vec_add(t_pt pt1, t_pt pt2)
{
	t_pt	sum;

	sum.x = pt1.x + pt2.x;
	sum.y = pt1.y + pt2.y;
	sum.z = pt1.z + pt2.z;
	sum.color = pt1.color;
	return (sum);
}

t_pt	vec_sub(t_pt pt1, t_pt pt2)
{
	t_pt	diff;

	diff.x = pt1.x - pt2.x;
	diff.y = pt1.y - pt2.y;
	diff.z = pt1.z - pt2.z;
	diff.color = pt1.color;
	return (diff);
}
