/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/21 16:25:26 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	reset(t_view *v, int k)
{
	if (k != BTN_R)
		return ;
	if (v->fract.type == fr_julia)
		setup_julia(&v->fract);
	else if (v->fract.type == fr_mandelbrot)
		setup_mandelbrot(&v->fract);
	else if (v->fract.type == fr_newton)
		setup_newton(&v->fract);
	v->fract.max_iter = 25;
	v->fract.smooth = true;
}

int			key_press(int k, t_view *v)
{
	reset(v, k);
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
		k == BTN_W || k == BTN_E || (k == BTN_H && !v->help) || k == BTN_R)
		draw_fractal(v);
	return (1);
}

int			key_release(int k, t_view *v)
{
	if (k == BTN_LSHIFT || k == BTN_RSHIFT)
		v->shift = false;
	return (1);
}
