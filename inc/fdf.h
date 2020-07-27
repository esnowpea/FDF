/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:24:34 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/27 16:25:59 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <limits.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define WIN_HEIGHT		1000
# define WIN_WIDTH		2000
# define ESC			53
# define LEFT_MOUSE 	1
# define MIDDLE_MOUSE 	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define I				34
# define CTRL			256
# define PLUS			69
# define MINUS			78

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
	double				r;
	double				fi;
	double				tet;
	int					xp;
	int					yp;
	int					color;
}						t_point;

typedef struct			s_line
{
	int					dx;
	int					dy;
	double				ds;
	int					sign_x;
	int					sign_y;
	int					error;
	int					derror;
	double				step_r;
	double				step_g;
	double				step_b;
	double				color_r;
	double				color_g;
	double				color_b;
}						t_line;

typedef struct			s_img
{
	void				*img_ptr;
	char				*data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_img;

typedef struct			s_map
{
	t_point				**arr;
	t_point				m;
	t_point				x;
	t_point				y;
	t_point				v[3];
	int					mouse_press;
	int					ctrl_press;
	int					x_mouse;
	int					y_mouse;
	int					shift_x;
	int					shift_y;
	int					width;
	int					height;
	void				*mlx;
	void				*win;
	t_img				img;
}						t_map;

void					*free_fdf(t_map *a);
t_map					*read_map(char *av);
int						ft_atoi_base_16(char *str);
void					img_pixel_put(t_img *img, t_point p1);
void					img_line_put(t_img *img, t_point p1, t_point p2);
void					img_black(t_img *img);
double					sqr(double a);
double					angle(double fi);
double					length_r(t_point a);
void					vector_mod(t_point *a, double b);
void					up_to_low1(char **s);
t_point					fill_point(double x, double y, double z);
void					projection(t_map *fdf);
void					scale(t_map *fdf, double xy, double z);
int						mouse_move(int x, int y, void *param);
void					event_handler(void *param);
void					print_image(t_map *fdf);
int						key_press(int keycode, void *param);
int						key_release(int keycode, void *param);
int						mouse_press(int button, int x, int y, void *param);
int						mouse_release(int button, int x, int y, void *param);

#endif
