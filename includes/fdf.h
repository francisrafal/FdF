/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:50:01 by frafal            #+#    #+#             */
/*   Updated: 2022/11/22 14:30:09 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <X11/keysym.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define WIN_W	1280
# define WIN_H	720
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define WHITE	0x00FFFFFF
# define DGREEN	0x00006600
# define BLACK	0x00000000
# define ISO	0.6154

typedef struct s_pt
{
	float_t		x;
	float_t		y;
	float_t		z;
}			t_pt;

typedef struct s_map
{
	t_pt	*pt_arr;
	int		x_dim;
	int		y_dim;	
	int		space;
}			t_map;

typedef struct s_matrix3x3
{
	float_t		c1r1;
	float_t		c1r2;
	float_t		c1r3;
	float_t		c2r1;
	float_t		c2r2;
	float_t		c2r3;
	float_t		c3r1;
	float_t		c3r2;
	float_t		c3r3;
}			t_matrix3x3;	

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_map	*map;
}			t_data;

typedef struct s_rect
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
}			t_rect;

#endif
