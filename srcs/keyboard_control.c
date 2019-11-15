/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/15 15:31:06 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				key_press(int k, t_view *v)
{
	if (k == BTN_ESC)
		exit(0);
	else if (k == BTN_NUM_MIN)
		v->fract.max_iter = v->fract.max_iter == 1 ? 1 : v->fract.max_iter - 1;
	else if (k == BTN_NUM_PLUS)
		v->fract.max_iter++;
	else if (k == BTN_LSHIFT || k == BTN_RSHIFT)
		v->shift = true;
	else if (k == BTN_S)
		v->fract.smooth ^= true;
	if (k == BTN_NUM_MIN || k == BTN_NUM_PLUS || k == BTN_S)
		draw_fractal(v);
	return (1);
}

int			key_release(int k, t_view *v)
{
	if (k == BTN_LSHIFT || k == BTN_RSHIFT)
		v->shift = false;
	return (1);
}
