/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:23:08 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/10 18:50:19 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_black_image(t_map *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			fdf->img.data[i * 4 + 4 * WIN_WIDTH * j] = 0;
			fdf->img.data[i * 4 + 4 * WIN_WIDTH * j + 1] = 0;
			fdf->img.data[i * 4 + 4 * WIN_WIDTH * j + 2] = 0;
			fdf->img.data[i * 4 + 4 * WIN_WIDTH * j + 3] = 0;
			j++;
		}
		i++;
	}
}

double		length_r(t_point a)
{
	return (sqrt(sqr(a.x) + sqr(a.y) + sqr(a.z)));
}

void		print_side(t_map *fdf, int i, int j)
{
	int		sign_i;
	int		sign_j;
	int		max_i;
	int		max_j;
	int		tmp;

	sign_i = i == 0 ? 1 : -1;
	sign_j = j == 0 ? 1 : -1;
	max_i = i == 0 ? fdf->height : -1;
	max_j = j == 0 ? fdf->width : -1;
	tmp = j;
	while (i != max_i)
	{
		j = tmp;
		while (j != max_j)
		{
			if (i < (fdf->height - 1))
				mlx_line_put(fdf, fdf->arr[i][j], fdf->arr[i + 1][j]);
			if (j < (fdf->width - 1))
				mlx_line_put(fdf, fdf->arr[i][j], fdf->arr[i][j + 1]);
			j += sign_j;
		}
		i += sign_i;
	}
}

void		print_image(t_map *fdf)
{
	projection(fdf);
	if (fdf->m.fi > 0 && fdf->m.fi <= 180 && fdf->m.tet > 0)
		print_side(fdf, 0, 0);
	else if (fdf->m.fi > -180 && fdf->m.fi <= 0 && fdf->m.tet > 0)
		print_side(fdf, fdf->height - 1, fdf->width - 1);
	else if (fdf->m.fi > 0 && fdf->m.fi <= 180 && fdf->m.tet < 0)
		print_side(fdf, fdf->height - 1, fdf->width - 1);
	else if (fdf->m.fi > -180 && fdf->m.fi <= 0 && fdf->m.tet < 0)
		print_side(fdf, 0, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
	get_black_image(fdf);
}
