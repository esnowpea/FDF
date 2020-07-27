/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:23:28 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/27 16:10:37 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*split_nb(char *str, t_map *a, int y)
{
	int		i;

	i = 0;
	while (*str && i < a->width)
	{
		while (*str == ' ')
			str++;
		a->arr[y][i] = fill_point((double)(i % a->width) -
				(double)(a->width - 1) / 2,
				(double)y - (double)(a->height - 1) / 2,
				(double)ft_atoi_base_16(str));
		while (*str && *str != ' ' && *str != ',')
			str++;
		if (*str == ',')
			a->arr[y][i].color = ft_atoi_base_16(str + 1);
		else
			a->arr[y][i].color = 0xffffff;
		while (*str && *str != ' ')
			str++;
		i++;
	}
	if (i < a->width)
		return (free_fdf(a));
	return (a);
}

int		find_height(char *av)
{
	int		fd;
	int		i;
	char	*s;

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
	int		fd;
	int		nb;
	char	*s;
	char	*tmp;

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
	while (get_next_line(fd, &s) > 0)
		free(s);
	close(fd);
	return (nb);
}

t_map	*fill_map(char *av)
{
	t_map	*out;
	int		i;

	if (!(out = (t_map*)malloc(sizeof(t_map))))
		return (free_fdf(out));
	out->width = find_width(av);
	out->height = find_height(av);
	if (!(out->arr = (t_point**)malloc(sizeof(t_point) * out->height)))
		return (free_fdf(out));
	i = 0;
	while (i < out->height)
		if (!(out->arr[i++] = (t_point*)malloc(sizeof(t_point) * out->width)))
			return (free_fdf(out));
	return (out);
}

t_map	*read_map(char *av)
{
	int		fd;
	char	*s;
	int		i;
	t_map	*out;

	if (!(out = fill_map(av)))
		return (free_fdf(out));
	fd = open(av, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &s) > 0)
	{
		up_to_low1(&s);
		if (!(out = split_nb(s, out, i++)))
			return (free_fdf(out));
		free(s);
	}
	if (i == 0)
		return (free_fdf(out));
	close(fd);
	return (out);
}
