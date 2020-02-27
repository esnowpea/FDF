/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:24:34 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/27 15:38:30 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include "libft.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <limits.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define WIN_HEIGHT	1000
# define WIN_WIDTH	2000
# define ESC		53
# define LEFT		123
# define RIGHT		124
# define UP			126
# define DOWN		125
# define RIGHT_R	47
# define LEFT_R		43

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
	double 				r;
	double 				fi;
	double 				tet;
	int 				xp;
	int 				yp;
	int					color;
}						t_point;

typedef struct			s_line
{
	int					dx;
	int					dy;
	int					sign_x;
	int					sign_y;
	int					error;
	int					derror;
	int					color;
}						t_line;

typedef struct			s_map
{
	t_point 			*arr;
	t_point				m;
	t_point 			x;
	t_point 			y;
	int 				x_mouse;
	int 				y_mouse;
	int 				width;
	int 				height;
	void				*mlx;
	void				*win;
	void				*black_image;
}						t_map;

void					*free_fdf(t_map *a);
t_map					*read_map(char *av);
int						ft_atoi_base(char *str);
int						key_hook(int keycode, void *param);
void					mlx_line_put(void *mlx, void *win,
						t_point p1, t_point p2);
double					sqr(double a);
t_point					fill_point(double x, double y, double z);
void					projection(t_map *fdf);
int						mouse_move(int x, int y, void *param);

#endif
