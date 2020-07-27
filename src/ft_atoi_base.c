/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:28:16 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/27 16:25:59 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	up_to_low1(char **str)
{
	char	*s;
	int		i;

	s = *str;
	i = 0;
	while (s && s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
		i++;
	}
}

int		ft_atoi_base1(char *str, int base)
{
	int		minus;
	int		a;

	a = 0;
	minus = 1;
	while ((*str == '\n') || (*str == '\t') || (*str == '\v') || \
	(*str == ' ') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_strchr("0123456789abcdef", *str))
	{
		a = a * base + (int)(ft_strlen("0123456789abcdef") -
				ft_strlen(ft_strchr("0123456789abcdef", *str)));
		str++;
	}
	return (minus * a);
}

int		ft_atoi_base_16(char *str)
{
	if (*str == '0' && *(str + 1) != 'x' && *(str + 1) != ' ' &&
	*(str + 1) != '\0')
		return (ft_atoi_base1(str + 1, 8));
	else if (*str == '0' && *(str + 1) == 'x')
		return (ft_atoi_base1(str + 2, 16));
	else
		return (ft_atoi_base1(str, 10));
}
