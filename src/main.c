/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:23:55 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/10 09:54:22 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*free_fdf(t_map *a)
{
	if (a && a->arr)
		free(a->arr);
	if (a)
		free(a);
	return (0);
}

t_point	fill_point(double x, double y, double z)
{
	t_point		a;

	a.x = x;
	a.y = y;
	a.z = z;
	return (a);
}

void	initialization(t_map *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	fdf->img.img_ptr = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.data = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bpp,
			&fdf->img.size_l, &fdf->img.endian);
	fdf->m.r = 1;
	fdf->m.fi = -120.0 / 180 * M_PI;
	fdf->m.tet = 120.0 / 180 * M_PI;
	fdf->shift_x = WIN_WIDTH / 2;
	fdf->shift_y = WIN_HEIGHT / 2;
	fdf->m.x = fdf->m.r * sin(fdf->m.tet) * cos(fdf->m.fi);
	fdf->m.y = fdf->m.r * sin(fdf->m.tet) * sin(fdf->m.fi);
	fdf->m.z = fdf->m.r * cos(fdf->m.tet);
	scale(fdf, 1.0 / 2 * WIN_WIDTH / fdf->width, 1.0 / 12 * WIN_WIDTH /
	fdf->width);
}

int		main(int ac, char **av)
{
	t_map	*fdf;

	if (ac > 2)
		return (0);
	if (!(fdf = read_map(av[1])))
		return (0);
	initialization(fdf);
	print_image(fdf);
	event_handler((void*)fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
