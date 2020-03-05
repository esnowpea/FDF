/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:44:34 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/05 20:48:52 by esnowpea         ###   ########.fr       */
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

	if (fdf->m.z > 0)
		a = vector_mult(fdf->m, fill_point(cos(fdf->m.fi), sin(fdf->m.fi), 0));
	else if (fdf->m.z < 0)
		a = vector_mult(fill_point(cos(fdf->m.fi), sin(fdf->m.fi), 0), fdf->m);
	else
		a = fdf->x;
	return (a);
}

t_point 	get_y(t_map *fdf)
{
	return (vector_mult(fdf->x, fdf->m));
}

double length_r(t_point a)
{
	return (sqrt(sqr(a.x) + sqr(a.y) + sqr(a.z)));
}

void		projection(t_map *fdf)
{
	double		p;
	int			i;

	fdf->x = get_x(fdf);
	p = length_r(fdf->x);
	fdf->x.x /= p;
	fdf->x.y /= p;
	fdf->x.z /= p;
	fdf->y = get_y(fdf);
	p = length_r(fdf->y);
	fdf->y.x /= p;
	fdf->y.y /= p;
	fdf->y.z /= p;
	printf("m:  x = %f, y = %f, z = %f\n", fdf->m.x, fdf->m.y, fdf->m.z);
	printf("x:  x = %f, y = %f, z = %f\n", fdf->x.x, fdf->x.y, fdf->x.z);
	printf("y:  x = %f, y = %f, z = %f\n", fdf->y.x, fdf->y.y, fdf->y.z);
	printf("fi = %f, tet = %f\n", fdf->m.fi * 180 / M_PI, fdf->m.tet * 180 /
														  M_PI);
	i = 0;
	while (i < (fdf->width * fdf->height))
	{
		fdf->arr[i].xp = (int)(fdf->arr[i].x * fdf->x.x +
				fdf->arr[i].y * fdf->y.x +
				fdf->arr[i].z * fdf->m.x) + WIN_WIDTH / 2;
		fdf->arr[i].yp = (int)(fdf->arr[i].x * fdf->x.y +
				fdf->arr[i].y * fdf->y.y +
				fdf->arr[i].z * fdf->m.y) + WIN_HEIGHT / 2;
		i++;
	}
}
