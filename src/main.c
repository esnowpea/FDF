/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:23:55 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/26 18:18:00 by esnowpea         ###   ########.fr       */
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
	fdf->m.x = 5;
	fdf->m.y = 5;
	fdf->m.z = 5;
	while (i < (fdf->width * fdf->height))
	{
		printf("x = %f, y = %f, z = %f\n", fdf->arr[i].x, fdf->arr[i].y,
				fdf->arr[i].z);
//		if (i % fdf->width < (fdf->width - 1))
//		{
//			mlx_line_put(fdf->mlx, fdf->win, fdf->arr[i],
//						 fdf->arr[i + 1]);
//		}
//		if (i / fdf->width < (fdf->height - 1))
//			mlx_line_put(fdf->mlx, fdf->win, fdf->arr[i],
//						 fdf->arr[i + fdf->width]);
		i++;
	}
	mlx_key_hook(fdf->win, key_hook, (void*)(&fdf));
	mlx_loop(fdf->mlx);
	return (0);
}
