/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:29:56 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/27 15:57:34 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int keycode, void *param)
{
	t_map	*fdf;
	int		i;

	fdf = (t_map *)param;
	if (keycode == ESC)
		exit(0);
	if (keycode == LEFT)
		fdf->m.fi -= 3.0 / 360 * M_PI;
	if (keycode == RIGHT)
		fdf->m.fi += 3.0 / 360 * M_PI;
	if (keycode == UP)
		fdf->m.tet += 3.0 / 360 * M_PI;
	if (keycode == DOWN)
		fdf->m.tet -= 3.0 / 360 * M_PI;
	if (keycode == RIGHT_R)
		fdf->m.z += 1;
	if (keycode == LEFT_R)
		fdf->m.z -= 1;
	fdf->m.x = fdf->m.r * sin(fdf->m.tet) * cos(fdf->m.fi);
	fdf->m.y = fdf->m.r * sin(fdf->m.tet) * sin(fdf->m.fi);
	fdf->m.z = fdf->m.r * cos(fdf->m.tet);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->black_image, 0,0);
	projection(fdf);
	i = 0;
	while (i < (fdf->width * fdf->height))
	{
//		printf("xp = %4d, yp = %4d, color = %#x\n", fdf->arr[i].xp,
//			   fdf->arr[i].yp, fdf->arr[i].color);
		if (i % fdf->width < (fdf->width - 1))
		{
			mlx_line_put(fdf->mlx, fdf->win, fdf->arr[i],
						 fdf->arr[i + 1]);
		}
		if (i / fdf->width < (fdf->height - 1))
			mlx_line_put(fdf->mlx, fdf->win, fdf->arr[i],
						 fdf->arr[i + fdf->width]);
		i++;
	}
	return (1);
}

int		mouse_move(int x, int y, void *param)
{
	t_map	*fdf;
	int		i;

	fdf = (t_map *)param;

}