/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:44:34 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/28 15:12:01 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		vector_mult(t_point a, t_point b)
{
	t_point out;

	out.x = a.y * b.z - a.z * b.y;
	out.y = a.z * b.x - a.x * b.z;
	out.z = a.x * b.y - a.y * b.x;
	return (out);
}

t_point 	get_x(t_map *fdf)
{
	t_point a;

	if (fdf->m.z < 0.0001 && fdf->m.z > -0.0001)
	{
		printf("pi / 2 = %f, tet = %f\n", M_PI / 2, fdf->m.tet);
		a = fdf->x;
	}
	else if (fdf->m.z > 0)
		a = vector_mult(fdf->m, fill_point(cos(fdf->m.fi), sin(fdf->m.fi), 0));
	else
		a = vector_mult(fill_point(cos(fdf->m.fi), sin(fdf->m.fi), 0), fdf->m);
	return (a);
}

t_point 	get_y(t_map *fdf)
{
	return (vector_mult(fdf->m, fdf->x));
}

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
	printf("fi = %f, tet = %f\n\n", fdf->m.fi * 180 / M_PI, fdf->m.tet * 180 /
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
		fdf->arr[i].yp = (int)((fdf->y.x * a.x + fdf->y.y * a.y +
				fdf->y.z * a.z) / length_r(fdf->y)) + WIN_HEIGHT / 2;
		i++;
	}
}
