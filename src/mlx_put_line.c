/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:38:07 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/06 18:34:08 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		sqr(double a)
{
	return (a * a);
}

double		step_color_r(int color1, int color2, double step, int r)
{
	return (((color1 >> r & 0xff) - (color2 >> r & 0xff)) / step);
}

t_line		get_start(t_point p1, t_point p2)
{
	t_line		line;

	line.dx = abs(p1.xp - p2.xp);
	line.dy = abs(p1.yp - p2.yp);
	line.ds = sqrt(sqr(line.dx) + sqr(line.dy));
	line.sign_x = p1.xp < p2.xp ? 1 : -1;
	line.sign_y = p1.yp < p2.yp ? 1 : -1;
	line.error = line.dx - line.dy;
	line.color_r = (p1.color >> 16 & 0xff);
	line.color_g = (p1.color >> 8 & 0xff);
	line.color_b = (p1.color >> 0 & 0xff);
	return (line);
}

void		mlx_line_put(void *mlx, void *win, t_point p1, t_point p2)
{
	t_line		line;

	line = get_start(p1, p2);
	while (p1.xp != p2.xp || p1.yp != p2.yp)
	{
		line.color_r -= step_color_r(p1.color, p2.color, line.ds, 16);
		line.color_g -= step_color_r(p1.color, p2.color, line.ds, 8);
		line.color_b -= step_color_r(p1.color, p2.color, line.ds, 0);
		p1.color = ((int)line.color_r << 16) +
				((int)line.color_g << 8) + (int)line.color_b;
		mlx_pixel_put(mlx, win, p1.xp, p1.yp, p1.color);
		line.derror = line.error * 2;
		if (line.derror > -line.dy)
		{
			line.error -= line.dy;
			p1.xp += line.sign_x;
		}
		if (line.derror < line.dx)
		{
			line.error += line.dx;
			p1.yp += line.sign_y;
		}
	}
}
