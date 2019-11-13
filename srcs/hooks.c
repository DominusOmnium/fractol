/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/13 17:36:45 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_press(int b, int x, int y, t_view *v)
{
	long double	deltax;
	long double	deltay;
	
	deltax = (v->fract.x_end - v->fract.x_start) * 0.01;
	deltay = (v->fract.y_end - v->fract.y_start) * 0.01;
	if (b == BTN_MOUSE_WHEEL_DOWN)
	{
		v->fract.x_start += deltax;
		v->fract.x_end -= deltax;
		v->fract.y_start += deltay;
		v->fract.y_end -= deltay;
	}
	else if (b == BTN_MOUSE_WHEEL_UP)
	{
		v->fract.x_start -= deltax;
		v->fract.x_end += deltax;
		v->fract.y_start -= deltay;
		v->fract.y_end += deltay;
	}
	if (b == BTN_MOUSE_LEFT && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		v->mouse.is_pressed = true;
		v->mouse.prev_x = x;
		v->mouse.prev_y = y;
	}
	v->fract.p_width = (v->fract.x_end - v->fract.x_start) / WIDTH;
    v->fract.p_height = (v->fract.y_end - v->fract.y_start) / HEIGHT;
	draw_fractal(v);
	return (1);
}

int				mouse_release(int b, int x, int y, t_view *v)
{
	(void)x;
	(void)y;
	if (b == BTN_MOUSE_LEFT)
		v->mouse.is_pressed = false;
	return (1);
}

int				key_press(int k, t_view *v)
{
	if (k == BTN_ESC)
		exit (0);
	else if (k == BTN_A)
		v->fract.max_iter = v->fract.max_iter == 1 ? 1 : v->fract.max_iter - 1;
	else if (k == BTN_S)
		v->fract.max_iter++;
	draw_fractal(v);
	return (1);
}

int				mouse_move(int x, int y, t_view *v)
{
	long double	dx;
	long double	dy;

	if (v->mouse.is_pressed == false)
		return (1);
	dx = (x - v->mouse.prev_x) * v->fract.p_height;
	dy = (y - v->mouse.prev_y) * v->fract.p_width;
	v->fract.x_start -= dx;
	v->fract.x_end -= dx;
	v->fract.y_start -= dy;
	v->fract.y_end -= dy;
	v->mouse.prev_x = x;
	v->mouse.prev_y = y;
	draw_fractal(v);
	return (1);
}
