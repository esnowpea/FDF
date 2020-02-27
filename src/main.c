/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:23:55 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/27 17:57:30 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	*free_fdf(t_map *a)
{
	if (a && a->arr)
		free(a->arr);
	if (a)
		free(a);
	return (0);
}

void	scale(t_map *fdf, int x, int y, int z)
{
	int		i;

	i = 0;
	while (i < fdf->height * fdf->width)
	{
		fdf->arr[i].x *= x;
		fdf->arr[i].y *= y;
		fdf->arr[i].z *= z;
		i++;
	}
}

int main(int ac, char **av)
{
	t_map	*fdf;

	if (ac > 2)
		return (0);
	fdf = read_map(av[1]);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "test");
	fdf->black_image = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	int i = 0;
	fdf->m.r = 1;
	fdf->m.fi = 45.0 / 360 * M_PI;
	fdf->m.tet = 45.0 / 360 * M_PI;
	fdf->m.x = fdf->m.r * sin(fdf->m.tet) * cos(fdf->m.fi);
	fdf->m.y = fdf->m.r * sin(fdf->m.tet) * sin(fdf->m.fi);
	fdf->m.z = fdf->m.r * cos(fdf->m.tet);
	fdf->x_mouse = WIN_WIDTH / 2;
	fdf->y_mouse = WIN_HEIGHT / 2;
	scale(fdf, 30, 30, 5);
	projection(fdf);
	while (i < (fdf->width * fdf->height))
	{
		printf("xp = %4d, yp = %4d, color = %#x\n", fdf->arr[i].xp,
				fdf->arr[i].yp, fdf->arr[i].color);
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
	mlx_hook(fdf->win, 6, 1, mouse_move, (void*)(fdf));
	mlx_key_hook(fdf->win, key_hook, (void*)(fdf));
	mlx_loop(fdf->mlx);
	return (0);
}
