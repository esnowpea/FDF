/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:29:56 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/12 11:57:53 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press(int keycode, void *param)
{
	t_map	*fdf;

	fdf = (t_map *)param;
	if (keycode == ESC)
		exit(0);
	if (keycode == I)
	{
		fdf->m.fi = -120.0 / 180 * M_PI;
		fdf->m.tet = -120.0 / 180 * M_PI;
		fdf->shift_x = WIN_WIDTH / 2;
		fdf->shift_y = WIN_HEIGHT / 2;
	}
	if (keycode == CTRL)
		fdf->ctrl_press = 1;
	if (keycode == PLUS)
		scale(fdf, 1, 1.1);
	if (keycode == MINUS)
		scale(fdf, 1, 0.9);
	print_image(fdf);
	return (1);
}

int		key_release(int keycode, void *param)
{
	t_map	*fdf;

	fdf = (t_map *)param;
	if (keycode == CTRL)
		fdf->ctrl_press = 0;
	return (1);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_map	*fdf;

	fdf = (t_map *)param;
	if (button == MIDDLE_MOUSE)
	{
		fdf->ctrl_press = 1;
		fdf->mouse_press = 1;
		fdf->x_mouse = x;
		fdf->y_mouse = y;
	}
	if (button == LEFT_MOUSE)
	{
		fdf->mouse_press = 1;
		fdf->x_mouse = x;
		fdf->y_mouse = y;
	}
	if (button == SCROLL_DOWN)
		scale(fdf, 1.1, 1.1);
	if (button == SCROLL_UP)
		scale(fdf, 0.9, 0.9);
	print_image(fdf);
	return (1);
}

int		mouse_move(int x, int y, void *param)
{
	t_map	*fdf;

	fdf = (t_map *)param;
	if (fdf->mouse_press && fdf->ctrl_press == 0)
	{
		fdf->m.fi -= (double)(x - fdf->x_mouse) / 10 / 180 * M_PI;
		fdf->m.tet -= (double)(y - fdf->y_mouse) / 10 / 180 * M_PI;
		fdf->m.fi = angle(fdf->m.fi);
		fdf->m.tet = angle(fdf->m.tet);
		fdf->x_mouse = x;
		fdf->y_mouse = y;
		fdf->m.x = fdf->m.r * sin(fdf->m.tet) * cos(fdf->m.fi);
		fdf->m.y = fdf->m.r * sin(fdf->m.tet) * sin(fdf->m.fi);
		fdf->m.z = fdf->m.r * cos(fdf->m.tet);
		print_image(fdf);
	}
	if (fdf->mouse_press && fdf->ctrl_press)
	{
		fdf->shift_x += x - fdf->x_mouse;
		fdf->shift_y += y - fdf->y_mouse;
		fdf->x_mouse = x;
		fdf->y_mouse = y;
		print_image(fdf);
	}
	return (1);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_map	*fdf;

	fdf = (t_map *)param;
	if (button == MIDDLE_MOUSE)
	{
		fdf->ctrl_press = 0;
		fdf->mouse_press = 0;
	}
	if (button == LEFT_MOUSE)
		fdf->mouse_press = 0;
	fdf->x_mouse = x;
	fdf->y_mouse = y;
	return (1);
}
