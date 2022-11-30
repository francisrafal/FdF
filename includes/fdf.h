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
# include <X11/X.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define WIN_W	1280
# define WIN_H	720
# define RED	0x00FF0000
# define DRED	0x00660000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define DBLUE	0x00000066
# define PURPLE	0x00B491C8
# define WHITE	0x00FFFFFF
# define DGREEN	0x00006600
# define BLACK	0x00000000
# define GREY	0x00888888
# define DGREY	0x00333333
# define GROUND_COLOR	RED
# define HIGH_COLOR		PURPLE
# define LOW_COLOR		DBLUE
# define ISO	0.6154

typedef struct s_pt
{
	float_t		x;
	float_t		y;
	float_t		z;
	int			color;
}			t_pt;

typedef struct s_map
{
	t_pt	*pt_arr;
	int		x_dim;
	int		y_dim;	
	int		space;
	int		min_height;
	int		max_height;
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
	t_pt	base_i;
	t_pt	base_j;
	t_pt	base_k;
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
	char	**parsed_file;
	int		animate_on;
	t_map	*original_map;
}			t_data;

void	img_pix_put(t_img *img, t_pt pt);
float_t	get_percentage(int start, int end, int cur);
int		calc_color_channel(int start, int end, float_t percentage);
int		get_color(t_pt cur, t_pt start, t_pt end, t_pt delta);
int		get_height_gradient_color(t_pt cur, t_pt start, t_pt end);
t_map	*generate_map(t_data *data);
t_map	*transform_map(t_map *map, t_matrix3x3 mat);
int		draw_line_low(t_img *img, t_pt start, t_pt end);
int		draw_line_high(t_img *img, t_pt start, t_pt end);
int		draw_line(t_img *img, t_pt start, t_pt end);
void	draw_map(t_img *img, t_map *map, t_pt offset);
void	render_background(t_img *img, int color);
int		loop_hook(t_data *data);
int		key_hook1(int keysym, t_data *data);
int		key_hook2(int keysym, t_data *data);
int		close_app(t_data *data);
void	replace_newline(unsigned int i, char *s);
int		print_parsed_file(char **parsed_file);
void	free_str_arr(char **str_arr);
int		count_cols(char *s);
t_pt	mat_mult(t_matrix3x3 mat, t_pt pt);
t_pt	vec_add(t_pt pt1, t_pt pt2);
int		parse_file(t_data *data, char *filename);
void	generate_iso_view(t_map *map);
int		start_mlx(t_data *data);
t_pt	vec_sub(t_pt pt1, t_pt pt2);
void	set_point_colors(t_map *map);
void	set_height_range(t_map *map, t_pt *cur);
void	fill_map(t_data *data, t_map *map);
void	zoom(t_map *map, float_t factor);
void	translate(t_map *map, t_pt offset);
void	rotate_x(t_map *map, float_t angle);
void	rotate_y(t_map *map, float_t angle);
void	scale_z(t_data *data, float_t factor);
char	*get_file(int fd, t_data *data);
int		lines_consistent(int cols, t_data *data);
void	append_line_to_file(char **line, char **file);
void	render_instructions(t_data *data, int color);
void	autoscale(t_map *map);
t_map	*save_original_map(t_data *data);
void	restore_map(t_data *data);
void	set_xy_min_max(t_map *map);

#endif
