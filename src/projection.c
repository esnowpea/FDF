/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:44:34 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/27 16:25:59 by esnowpea         ###   ########.fr       */
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

t_point		get_x(t_map *fdf)
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

t_point		get_y(t_map *fdf)
{
	return (vector_mult(fdf->x, fdf->m));
}

void		projection1(t_map *fdf)
{
	double		det;

	fdf->x = get_x(fdf);
	fdf->y = get_y(fdf);
	vector_mod(&fdf->x, length_r(fdf->x));
	vector_mod(&fdf->y, length_r(fdf->y));
	det = fdf->x.x * fdf->y.y * fdf->m.z +
			fdf->y.x * fdf->m.y * fdf->x.z +
			fdf->y.z * fdf->m.x * fdf->x.y -
			fdf->y.y * fdf->m.x * fdf->x.z -
			fdf->y.z * fdf->m.y * fdf->x.x -
			fdf->y.x * fdf->m.z * fdf->x.y;
	fdf->v[0].x = (fdf->y.y * fdf->m.z - fdf->y.z * fdf->m.y) / det;
	fdf->v[0].y = (fdf->x.y * fdf->m.z - fdf->x.z * fdf->m.y) / det;
	fdf->v[0].z = (fdf->x.y * fdf->y.z - fdf->x.z * fdf->y.y) / det;
	fdf->v[1].x = (fdf->y.x * fdf->m.z - fdf->y.z * fdf->m.x) / det;
	fdf->v[1].y = (fdf->x.x * fdf->m.z - fdf->x.z * fdf->m.x) / det;
	fdf->v[1].z = (fdf->x.x * fdf->y.z - fdf->x.z * fdf->y.x) / det;
	fdf->v[2].x = (fdf->y.x * fdf->m.y - fdf->y.y * fdf->m.x) / det;
	fdf->v[2].y = (fdf->x.x * fdf->m.y - fdf->x.y * fdf->m.x) / det;
	fdf->v[2].z = (fdf->x.x * fdf->y.y - fdf->x.y * fdf->y.x) / det;
}

void		projection(t_map *fdf)
{
	int			i;
	int			j;

	fdf->m.x = fdf->m.r * sin(fdf->m.tet) * cos(fdf->m.fi);
	fdf->m.y = fdf->m.r * sin(fdf->m.tet) * sin(fdf->m.fi);
	fdf->m.z = fdf->m.r * cos(fdf->m.tet);
	projection1(fdf);
	i = 0;
	while (i < (fdf->height))
	{
		j = 0;
		while (j < fdf->width)
		{
			fdf->arr[i][j].xp = (int)(fdf->arr[i][j].x * fdf->v[0].x +
									fdf->arr[i][j].y * fdf->v[1].x +
									fdf->arr[i][j].z * fdf->v[2].x) +
									fdf->shift_x;
			fdf->arr[i][j].yp = (int)(fdf->arr[i][j].x * fdf->v[0].y +
									fdf->arr[i][j].y * fdf->v[1].y +
									fdf->arr[i][j].z * fdf->v[2].y) +
									fdf->shift_y;
			j++;
		}
		i++;
	}
}
