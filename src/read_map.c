/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:23:28 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/26 16:19:37 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	fill_point(double x, double y, double z)
{
	t_point		a;

	a.x = x;
	a.y = y;
	a.z = z;
	return (a);
}

t_map	*split_nb(char *str, t_map *a, int y)
{
	int		i;

	i = y * a->width;
	while (*str && i <= a->width * (y + 1))
	{
		while (*str == ' ')
			str++;
		a->arr[i] = fill_point((double)(i % a->width), (double)y, \
				(double)ft_atoi_base(str));
		while (*str && *str != ' ' && *str != ',')
			str++;
		if (*str == ',')
			a->arr[i].color = ft_atoi_base(str + 1);
		else
			a->arr[i].color = 0xffffff;
		while (*str && *str != ' ')
			str++;
		i++;
	}
	if (i < a->width * (y + 1))
		return (free_fdf(a));
	return (a);
}

int		find_height(char *av)
{
	int 	fd;
	int 	i;
	char 	*s;

	fd = open(av, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &s) > 0)
	{
		free(s);
		i++;
	}
	close(fd);
	return (i);
}

int		find_width(char *av)
{
	int 	fd;
	int 	nb;
	char 	*s;
	char 	*tmp;

	tmp = 0;
	fd = open(av, O_RDONLY);
	nb = 0;
	if (get_next_line(fd, &s) > 0)
	{
		tmp = s;
		while (*s)
		{
			while (*s == ' ')
				s++;
			nb++;
			while (*s && *s != ' ')
				s++;
		}
	}
	free(tmp);
	close(fd);
	return (nb);
}

t_map 	*read_map(char *av)
{
	int		fd;
	char 	*s;
	int 	i;
	t_map	*out;

	if (!(out = (t_map*)malloc(sizeof(t_map))))
		return (0);
	out->width = find_width(av);
	out->height = find_height(av);
	out->arr = (t_point*)malloc(sizeof(t_point) * out->height * out->width);
	if (!out->arr)
		return (free_fdf(out));
	fd = open(av, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &s) > 0)
	{
		out = split_nb(s, out, i++);
		free(s);
	}
	close(fd);
	return (out);
}