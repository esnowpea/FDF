/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:03:57 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/27 19:41:35 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale(t_map *fdf, double xy, double z)
{
	int		i;
	int		j;

	i = 0;
	while (i < (fdf->height))
	{
		j = 0;
		while (j < fdf->width)
		{
			fdf->arr[i][j].x *= xy;
			fdf->arr[i][j].y *= xy;
			fdf->arr[i][j].z *= z;
			j++;
		}
		i++;
	}
}

double	angle(double fi)
{
	while (fi > M_PI)
		fi -= 2 * M_PI;
	while (fi <= -1 * M_PI)
		fi += 2 * M_PI;
	return (fi);
}

void	vector_mod(t_point *a, double b)
{
	a->x /= b;
	a->y /= b;
	a->z /= b;
}

int		close_press(void *param)
{
	(void)param;
	exit(0);
}

void	event_handler(void *param)
{
	t_map	*fdf;

	fdf = (t_map*)param;
	mlx_hook(fdf->win, 2, 0, key_press, param);
	mlx_hook(fdf->win, 3, 0, key_release, param);
	mlx_hook(fdf->win, 17, 0, close_press, param);
	mlx_hook(fdf->win, 4, 0, mouse_press, param);
	mlx_hook(fdf->win, 6, 0, mouse_move, param);
	mlx_hook(fdf->win, 5, 0, mouse_release, param);
}
