/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:06:23 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/15 14:52:49 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double			mandelbrot(t_complex cxy, t_fractal f)
{
	t_complex	c;
	t_complex	c2;
	int			n;

	c.r = 0;
	c.i = 0;
	c2.r = 0;
	c2.i = 0;
	n = 0;
	while (c2.r + c2.i <= 256 && n < f.max_iter)
	{
		c.i = 2 * c.r * c.i + cxy.i;
		c.r = c2.r - c2.i + cxy.r;
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		n++;
	}
	return (n + (f.smooth == 1 ? 1 - log(log2(fabsl(c2.r + c2.i))) : 0));
}

void				setup_mandelbrot(t_fractal *f)
{
	f->type = fr_mandelbrot;
	f->r_start = -2;
	f->r_end = 2;
	f->i_start = 0 - (f->r_end - f->r_start) / 2 * HEIGHT / (double)WIDTH;
	f->i_end = 0 + (f->r_end - f->r_start) / 2 * HEIGHT / (double)WIDTH;
	f->p_width = (f->r_end - f->r_start) / WIDTH;
	f->p_height = (f->i_end - f->i_start) / HEIGHT;
}
