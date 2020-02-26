/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:38:07 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/26 16:42:41 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	sqr(double a)
{
	return (a * a);
}

int 	step_color(int color1, int color2, double step)
{
	int color;
	color = (int)(((color1 & 0xff0000) - (color2 & 0xff0000)) / step / 65536)
			* 65536 + (int)(((color1 & 0x00ff00) - (color2 & 0x00ff00)) /
							step / 256) * 256 + (int)(((color1 & 0x0000ff) -
							(color2 & 0x0000ff)) / step);
	return (color);
}

void		mlx_line_put(void *mlx, void *win, t_point p1, t_point p2)
{
	t_line		line;

	line.dx = abs(p1.xp - p2.xp);
	line.dy = abs(p1.yp - p2.yp);
	line.sign_x = p1.xp < p2.xp ? 1 : -1;
	line.sign_y = p1.yp < p2.yp ? 1 : -1;
	line.error = line.dx - line.dy;
	line.color = step_color(p1.color, p2.color,
			sqrt(sqr(line.dx) + sqr(line.dy)));
	while (p1.xp != p2.xp || p1.yp != p2.yp)
	{
		p1.color -= line.color;
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