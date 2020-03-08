/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:38:07 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/08 14:55:55 by esnowpea         ###   ########.fr       */
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

void		get_color(t_map *fdf, t_line *line, t_point p1, t_point p2)
{
	line->color_r -= step_color_r(p1.color, p2.color, line->ds, 16);
	line->color_g -= step_color_r(p1.color, p2.color, line->ds, 8);
	line->color_b -= step_color_r(p1.color, p2.color, line->ds, 0);
	if (p1.xp >= 0 && p1.xp <= WIN_WIDTH && p1.yp >= 0 && p1.yp <= WIN_HEIGHT)
	{
		fdf->img.data[p1.xp * 4 + 4 * WIN_WIDTH * p1.yp] =
				(char)(line->color_b);
		fdf->img.data[p1.xp * 4 + 4 * WIN_WIDTH * p1.yp + 1] =
				(char)(line->color_g);
		fdf->img.data[p1.xp * 4 + 4 * WIN_WIDTH * p1.yp + 2] =
				(char)(line->color_r);
	}
}

void		mlx_line_put(t_map *fdf, t_point p1, t_point p2)
{
	t_line		line;

	line = get_start(p1, p2);
	while (p1.xp != p2.xp || p1.yp != p2.yp)
	{
		get_color(fdf, &line, p1, p2);
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
