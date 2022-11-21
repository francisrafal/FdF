/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:50:01 by frafal            #+#    #+#             */
/*   Updated: 2022/11/21 14:45:33 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <X11/keysym.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define GREEN 0x0000FF00

typedef struct	s_data {
	void		*mlx_ptr;
	void		*win_ptr;
}				t_data;

#endif
