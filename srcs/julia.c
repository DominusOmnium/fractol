/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:07:58 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/15 14:51:04 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double			julia(int x, int y, t_complex cxy, t_view *v)
{
	t_complex	c;
	t_complex	c2;
	long double	n;

	c = screen_to_complex(x, y, v);
	c2.r = c.r * c.r;
	c2.i = c.i * c.i;
	n = 0;
	while (c2.r + c2.i < 256 && n < v->fract.max_iter)
	{
		c.i = 2 * c.r * c.i + cxy.i;
		c.r = c2.r - c2.i + cxy.r;
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		n++;
	}
	if (n == v->fract.max_iter)
		return (n);
	return (n + (v->fract.smooth == 1 ? 1 - log(log2(fabsl(c2.r + c2.i))) : 0));
}

void				setup_julia(t_fractal *f)
{
	f->type = fr_julia;
	f->r_start = -2;
	f->r_end = 2;
	f->i_start = -2;
	f->i_end = f->i_start + (f->r_end - f->r_start) * HEIGHT / (double)WIDTH;
	f->p_width = (f->r_end - f->r_start) / WIDTH;
	f->p_height = (f->i_end - f->i_start) / HEIGHT;
}
