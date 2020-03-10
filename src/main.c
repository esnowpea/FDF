/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:23:55 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/10 19:12:17 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*free_fdf(t_map *a)
{
	int		i;

	write(1, "No data found.\n", 15);
	if (a && a->arr)
	{
		i = 0;
		while (i < a->height)
		{
			if (a->arr[i])
				free(a->arr[i]);
			i++;
		}
	}
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
	fdf->m.tet = -120.0 / 180 * M_PI;
	fdf->shift_x = WIN_WIDTH / 2;
	fdf->shift_y = WIN_HEIGHT / 2;
	scale(fdf, 1.0 / 2 * WIN_WIDTH / fdf->width, 1.0 / 12 * WIN_WIDTH /
	fdf->width);
}

int		main(int ac, char **av)
{
	t_map	*fdf;

	if (ac != 2)
	{
		write(1, "Usage: ",7);
		write(1, av[0],ft_strlen(av[0]));
		write(1, " <filename>\n",12);
		return (0);
	}
	if (!(fdf = read_map(av[1])))
		exit(0);
	initialization(fdf);
	print_image(fdf);
	event_handler((void*)fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
