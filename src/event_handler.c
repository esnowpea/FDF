/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:03:57 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/06 18:46:50 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale(t_map *fdf, double xy, double z)
{
	int		i;

	i = 0;
	while (i < fdf->height * fdf->width)
	{
		fdf->arr[i].x *= xy;
		fdf->arr[i].y *= xy;
		fdf->arr[i].z *= z;
		i++;
	}
}

void	print_image(t_map *fdf)
{
	int		i;

	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->black_image, 0, 0);
	projection(fdf);
	i = 0;
	while (i < (fdf->width * fdf->height))
	{
		if (i % fdf->width < (fdf->width - 1))
		{
			mlx_line_put(fdf->mlx, fdf->win, fdf->arr[i], fdf->arr[i + 1]);
		}
		if (i / fdf->width < (fdf->height - 1))
			mlx_line_put(fdf->mlx, fdf->win, fdf->arr[i],
					fdf->arr[i + fdf->width]);
		i++;
	}
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
	mlx_hook(fdf->win, 2, 0, key_press, (void*)(fdf));
	mlx_hook(fdf->win, 3, 0, key_release, (void*)(fdf));
	mlx_hook(fdf->win, 17, 0, close_press, (void*)(fdf));
	mlx_hook(fdf->win, 4, 0, mouse_press, (void*)(fdf));
	mlx_hook(fdf->win, 6, 0, mouse_move, (void*)(fdf));
	mlx_hook(fdf->win, 5, 0, mouse_release, (void*)(fdf));
}
