/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/04 12:55:37 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	move_handler(t_view *v, int k)
{
	if (k != BTN_RIGHT && k != BTN_LEFT && k != BTN_UP && k != BTN_DOWN)
		return (0);
	if (k == BTN_LEFT)
	{
		v->fract.r_start -= (v->fract.r_end - v->fract.r_start) * 0.05;
		v->fract.r_end -= (v->fract.r_end - v->fract.r_start) * 0.05;
	}
	else if (k == BTN_RIGHT)
	{
		v->fract.r_start += (v->fract.r_end - v->fract.r_start) * 0.05;
		v->fract.r_end += (v->fract.r_end - v->fract.r_start) * 0.05;
	}
	else if (k == BTN_UP)
	{
		v->fract.i_start -= (v->fract.i_end - v->fract.i_start) * 0.05;
		v->fract.i_end -= (v->fract.i_end - v->fract.i_start) * 0.05;
	}
	else if (k == BTN_DOWN)
	{
		v->fract.i_start += (v->fract.i_end - v->fract.i_start) * 0.05;
		v->fract.i_end += (v->fract.i_end - v->fract.i_start) * 0.05;
	}
	return (1);
}

static int	rmc_handler(t_view *v, int k)
{
	if (move_handler(v, k) == 1)
		return (1);
	if (k == BTN_C && v->fract.type != fr_newton)
	{
		v->fract.color_type = (v->fract.color_type == 1) ? 2 : 1;
		return (1);
	}
	if (k != BTN_R)
		return (0);
	if (v->fract.type == fr_julia)
		setup_julia(&v->fract);
	else if (v->fract.type == fr_mandelbrot)
		setup_mandelbrot(&v->fract);
	else if (v->fract.type == fr_newton)
		setup_newton(&v->fract);
	v->fract.max_iter = 25;
	v->fract.smooth = true;
	return (1);
}

int			key_press(int k, t_view *v)
{
	if (k == BTN_ESC)
		exit(0);
	else if (k == BTN_NUM_MIN && !v->help)
		v->fract.max_iter = v->fract.max_iter == 1 ? 1 : v->fract.max_iter - 1;
	else if (k == BTN_NUM_PLUS && !v->help)
		v->fract.max_iter++;
	else if (k == BTN_LSHIFT || k == BTN_RSHIFT)
		v->shift = true;
	else if (k == BTN_S && !v->help)
		v->fract.smooth ^= true;
	else if (k == BTN_H)
		v->help ^= true;
	else if (k == BTN_Q && !v->help)
		v->draw_type = gpu_parallel;
	else if (k == BTN_W && !v->help)
		v->draw_type = cpu_parallel;
	else if (k == BTN_E && !v->help)
		v->draw_type = cpu;
	if (k == BTN_H && v->help)
		draw_help(v);
	if (k == BTN_NUM_MIN || k == BTN_NUM_PLUS || k == BTN_S || k == BTN_Q ||
		k == BTN_W || k == BTN_E || (k == BTN_H && !v->help) || k == BTN_R ||
		rmc_handler(v, k) == 1)
		draw_fractal(v);
	return (1);
}

int			key_release(int k, t_view *v)
{
	if (k == BTN_LSHIFT || k == BTN_RSHIFT)
		v->shift = false;
	return (1);
}
