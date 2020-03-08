/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:23:28 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/08 13:42:44 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*split_nb(char *str, t_map *a, int y)
{
	int		i;

	i = y * a->width;
	while (*str && i <= a->width * (y + 1))
	{
		while (*str == ' ')
			str++;
		a->arr[i] = fill_point((double)(i % a->width - a->width / 2),
				(double)(y - a->height / 2), (double)ft_atoi_base(str));
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

	if (!(out = (t_map*)malloc(sizeof(t_map))))
		return (0);
	out->width = find_width(av);
	out->height = find_height(av);
	out->arr = (t_point*)malloc(sizeof(t_point) * out->height * out->width);
	if (!out->arr)
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
		return (0);
	fd = open(av, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &s) > 0)
	{
		up_to_low(&s);
		if (!(out = split_nb(s, out, i++)))
			return (0);
		free(s);
	}
	if (i == 0)
	{
		write(1, "No data found.\n", 15);
		return (0);
	}
	close(fd);
	return (out);
}
