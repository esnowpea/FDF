/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:24:34 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/08 14:36:19 by esnowpea         ###   ########.fr       */
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
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define LEFT			123
# define RIGHT			124
# define UP				126
# define DOWN			125
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
	t_point				*arr;
	t_point				m;
	t_point				x;
	t_point				y;
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
int						ft_atoi_base(char *str);
void					mlx_line_put(t_map *fdf, t_point p1, t_point p2);
double					sqr(double a);
void					up_to_low(char **s);
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
