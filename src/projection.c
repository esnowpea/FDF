/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:44:34 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/27 19:15:30 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 		compare_zero(double a)
{
	if (a > 0.00001 || a < -0.00001)
		return (1);
	else
		return (0);
}

t_point		vector_mult(t_point a, t_point b)
{
	t_point out;

	out.x = a.y * b.z - a.z * b.y;
	out.y = a.z * b.x - a.x * b.z;
	out.z = a.x * b.y - a.y * b.x;
	return (out);
}
/*
t_point 	get_x(t_map *fdf)
{
	t_point	a;

	if (compare_zero(fdf->m.y) == 0 && compare_zero(fdf->m.x) != 0)
		a = fill_point(0, fdf->m.x > 0 ? -1 : 1, 0);
	else if (compare_zero(fdf->m.y) != 0 && compare_zero(fdf->m.x) == 0)
		a = fill_point(fdf->m.y > 0 ? 1 : -1, 0, 0);
	else if (compare_zero(fdf->m.y) != 0 && compare_zero(fdf->m.x) != 0)
	{
		a.x = 1;//fdf->m.y > 0 ? 1 : -1;
		a = fill_point(a.x, -a.x * fdf->m.x / fdf->m.y, 0);
	}
	else
		a = fdf->x;
	return (a);
}
*/
t_point 	get_x(t_map *fdf)
{
	t_point a;


	if (fdf->m.y != 0 && fdf->m.x != 0)
		a = vector_mult(fill_point(0, 0, 1), fdf->m);
	else
		a = fdf->x;
	return (a);
}

t_point 	get_y(t_map *fdf)
{
	return (vector_mult(fdf->m, fdf->x));
}
/*
t_point 	get_y(t_map *fdf)
{
	t_point	b;

	if (compare_zero(fdf->x.y) != 0 && compare_zero(fdf->m.z) != 0)
	{
		b.x = fdf->m.x * fdf->m.z > 0 ? -1 : 1;
		b = fill_point(b.x, -b.x * fdf->x.x / fdf->x.y, \
        -b.x * (fdf->m.x - fdf->x.x / fdf->x.y * fdf->m.y) / fdf->m.z);
	}
	else if (compare_zero(fdf->m.z) != 0 && compare_zero(fdf->x.y) == 0)
	{
		b.y = fdf->m.z >= 0 ? -1 : 1;
		b = fill_point(0, b.y, -b.y * fdf->m.y / fdf->m.z);
	}
	else if (compare_zero(fdf->m.z) == 0)
		b = fill_point(0, 0, fdf->m.z > 0 ? -1 : 1);
	else if (compare_zero(fdf->x.y) != 0)
	{
		if ((fdf->m.z > 0 && fdf->x.y > 0) || (fdf->m.z < 0 && fdf->x.x < 0))
			b.x = -1;
		else
			b.x = 1;
		b = fill_point(b.x, -b.x * fdf->x.x / fdf->x.y, 0);
	}
	else
		b = fill_point(0, 1, 0);
	return (b);
}
*/
/*
t_point 	get_x(t_map *fdf)
{
	t_point	a;

	if (compare_zero(fdf->m.y) == 0)
		a = fill_point(0, -1, 0);
	else if (compare_zero(fdf->m.y) != 0 && compare_zero(fdf->m.x) != 0)
	{
		a.x = 1;
		a = fill_point(a.x, -a.x * fdf->m.x / fdf->m.y, 0);
	}
	else if (compare_zero(fdf->m.x) == 0)
		a = fill_point(1, 0, 0);
	else
		a = fdf->x;
	return (a);
}

t_point 	get_y(t_map *fdf)
{
	t_point	b;

	if (compare_zero(fdf->x.y) != 0 && compare_zero(fdf->m.z) != 0)
	{
		b.x = fdf->m.z > 0 ? -1 : 1;
		b = fill_point(b.x, -b.x * fdf->x.x / fdf->x.y, \
        -b.x * (fdf->m.x - fdf->x.x / fdf->x.y * fdf->m.y) / fdf->m.z);
	}
	else if (compare_zero(fdf->m.z) != 0 && compare_zero(fdf->x.y) == 0)
	{
		b.y = fdf->m.z > 0 ? -1 : 1;
		b = fill_point(0, b.y, -b.y * fdf->m.y / fdf->m.z);
	}
	else if (compare_zero(fdf->m.z) == 0)
		b = fill_point(0, 0, fdf->m.z > 0 ? -1 : 1);
	else if (compare_zero(fdf->x.y) != 0)
	{
		if ((fdf->m.z > 0 && fdf->x.y > 0) || (fdf->m.z < 0 && fdf->x.x < 0))
			b.x = -1;
		else
			b.x = 1;
		b = fill_point(b.x, -b.x * fdf->x.x / fdf->x.y, 0);
	}
	else
		b = fill_point(0, 1, 0);
	return (b);
}
*/
double length_r(t_point a)
{
	return (sqrt(sqr(a.x) + sqr(a.y) + sqr(a.z)));
}

void		projection(t_map *fdf)
{
	double		p;
	t_point		a;
	int			i;

	fdf->x = get_x(fdf);
	fdf->y = get_y(fdf);
	printf("m:  x = %f, y = %f, z = %f\n", fdf->m.x, fdf->m.y, fdf->m.z);
	printf("x:  x = %f, y = %f, z = %f\n", fdf->x.x, fdf->x.y, fdf->x.z);
	printf("y:  x = %f, y = %f, z = %f\n", fdf->y.x, fdf->y.y, fdf->y.z);
	printf("fi = %f, tet = %f\n\n", fdf->m.fi * 360 / M_PI, fdf->m.tet * 360 /
	M_PI);
	i = 0;
	while (i < (fdf->width * fdf->height))
	{
		p = (fdf->m.x * fdf->arr[i].x + fdf->m.y * fdf->arr[i].y +
			 fdf->m.z * fdf->arr[i].z) /
			(sqr(fdf->m.x) + sqr(fdf->m.y) + sqr(fdf->m.z));
		a.x = fdf->arr[i].x - p * fdf->m.x;
		a.y = fdf->arr[i].y - p * fdf->m.y;
		a.z = fdf->arr[i].z - p * fdf->m.z;
		fdf->arr[i].xp = (int)((fdf->x.x * a.x + fdf->x.y * a.y +
				fdf->x.z * a.z) / length_r(fdf->x)) + WIN_WIDTH / 2;
		fdf->arr[i].yp = -(int)((fdf->y.x * a.x + fdf->y.y * a.y +
				fdf->y.z * a.z) / length_r(fdf->y)) + WIN_HEIGHT / 2;
		i++;
	}
}