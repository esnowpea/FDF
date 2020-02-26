/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:28:16 by esnowpea          #+#    #+#             */
/*   Updated: 2020/02/26 15:28:16 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 	ft_atoi_base1(char *str, int base)
{
	int 	minus;
	int		a;
	char	s[] = "0123456789abcdef";

	a = 0;
	minus = 1;
	while ((*str == '\n') || (*str == '\t') || (*str == '\v') || \
	(*str == ' ') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_strchr(s, *str))
	{
		a = a * base + (int)(ft_strlen(s) - ft_strlen(ft_strchr(s, *str)));
		str++;
	}
	return (minus * a);
}

int 	ft_atoi_base(char *str)
{
	if (*str == '0' && *(str + 1) != '\0')
		return (0);
	else if (*str == '0' && *(str + 1) != 'x')
		return (ft_atoi_base1(str + 1, 8));
	else if (*str == '0' && *(str + 1) == 'x')
		return (ft_atoi_base1(str + 2, 16));
	else
		return (ft_atoi_base1(str, 10));
}