/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:44:34 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/26 18:09:38 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point 	get_x(t_map *fdf)
{
	t_point	a;

	if (fdf->m.y == 0)
		a = fill_point(0, fdf->m.x > 0 ? 1 : -1, 0);
	else if (fdf->m.y != 0 && fdf->m.x != 0)
		a = fill_point(fdf->m.y > 0 ? -1 : 1, -a.x * fdf->m.x / fdf->m.y, 0);
	else
		a = fdf->x;
	return (a);
}

t_point 	get_y(t_map *fdf)
{
	t_point	b;

	if (fdf->x.y != 0 && fdf->m.z != 0)
		b = fill_point(fdf->m.x * fdf->m.z > 0 ? -1 : 1,\
		-b.x * fdf->x.x / fdf->x.y,\
		-b.x * (fdf->m.x - fdf->x.x / fdf->x.y * fdf->m.y) / fdf->m.z);
	else if (fdf->m.z != 0 && fdf->x.y == 0)
		b = fill_point(0, fdf->m.y * fdf->m.z > 0 ? -1 : 1,
				-b.y * fdf->m.y / fdf->m.z);
	else if (fdf->m.z == 0)
		b = fill_point(0, 0, 1);
	else if (fdf->x.y != 0)
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

void		projection(t_map *fdf)
{
	double		p;
	t_point		a;
	int			i;

	fdf->x = get_x(fdf);
	fdf->y = get_y(fdf);
	i = 0;
	while (i < (fdf->width * fdf->height))
	{
		p = (fdf->m.x * fdf->arr[i].x + fdf->m.y * fdf->arr[i].y +
			 fdf->m.z * fdf->arr[i].z) /
			(sqr(fdf->m.x) + sqr(fdf->m.y) + sqr(fdf->m.z));
		a.x = fdf->arr[i].x - p * fdf->m.x;
		a.y = fdf->arr[i].y - p * fdf->m.y;
		a.z = fdf->arr[i].z - p * fdf->m.z;
		fdf->arr[i].xp = (int)(fdf->x.x * a.x + fdf->x.y * a.y +
				fdf->x.z * a.z);
		fdf->arr[i].yp = (int)(fdf->y.x * a.x + fdf->y.y * a.y +
				fdf->y.z * a.z);
		i++;
	}
}